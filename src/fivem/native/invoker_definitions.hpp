#pragma once

#include "../includes/includes.hpp"
#include "../classes/classes.hpp"


inline constexpr char ToLower(const char c)
{
	return (c >= 'A' && c <= 'Z') ? (c - 'A' + 'a') : c;
}

// hash string, lowercase
inline constexpr uint32_t GET_HASH_KEY(const char* string)
{
	uint32_t hash = 0;

	for (; *string; ++string)
	{
		hash += ToLower(*string);
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}

	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);

	return hash;
}


struct scrVector2
{
	alignas(8) float x;
	alignas(8) float y;
	alignas(8) float z;
};

struct alignas(16) scrVec3N
{
	float x;
	float y;
	float z;
};

struct scrVectorSpace
{
	scrVector2* outVectors[4];
	scrVec3N inVectors[4];
};

class scrNativeCallContext
{
protected:
	void* m_pReturn; // +0
	uint32_t m_nArgCount; // +8
	void* m_pArgs; // +16

	uint32_t m_nDataCount; // +24

	// scratch space for vector things
	scrVectorSpace m_vectorSpace;
	uint8_t pad[96];

public:
	template<typename T>
	inline T GetArgument(int idx)
	{
		intptr_t* arguments = (intptr_t*)m_pArgs;

		return *(T*)&arguments[idx];
	}

	template<typename T>
	inline T SetArgument(int idx, uint64_t value)
	{
		intptr_t* arguments = (intptr_t*)m_pArgs;

		return *(T*)&arguments[idx] = value;
	}

	template<typename T>
	inline void SetResult(int idx, T value)
	{
		intptr_t* returnValues = (intptr_t*)m_pReturn;

		*(T*)&returnValues[idx] = value;
	}

	inline int GetArgumentCount()
	{
		return m_nArgCount;
	}

	template<typename T>
	inline T GetResult(int idx)
	{
		intptr_t* returnValues = (intptr_t*)m_pReturn;

		return *(T*)&returnValues[idx];
	}

	inline void* GetArgumentBuffer()
	{
		return m_pArgs;
	}

	// copy vector3 pointer results to the initial argument
	inline void SetVectorResults()
	{
		for (size_t i = 0; i < m_nDataCount; i++)
		{
			auto outVector = m_vectorSpace.outVectors[i];
			const auto& inVector = m_vectorSpace.inVectors[i];

			outVector->x = inVector.x;
			outVector->y = inVector.y;
			outVector->z = inVector.z;
		}
	}

	inline const scrVec3N* GetVector()
	{
		return &m_vectorSpace.inVectors[0];
	}
};

class NativeContextRaw :
	public scrNativeCallContext
{
public:
	inline NativeContextRaw(void* buffer, int argumentCount)
	{
		m_pArgs = buffer;
		m_pReturn = buffer;

		m_nArgCount = argumentCount;
		m_nDataCount = 0;
	}

	inline void SetArgumentCount(int argumentCount)
	{
		m_nArgCount = argumentCount;
	}
};

class NativeContext :
	public scrNativeCallContext
{
private:
	// Configuration
	enum
	{
		MaxNativeParams = 32,
		ArgSize = 8,
	};

	// Anything temporary that we need
	uint8_t m_TempStack[MaxNativeParams * ArgSize];

public:
	inline NativeContext()
	{
		m_pArgs = &m_TempStack;
		m_pReturn = &m_TempStack;		// It's okay to point both args and return at 
		// the same pointer. The game should handle this.
		m_nArgCount = 0;
		m_nDataCount = 0;

		memset(m_TempStack, 0, sizeof(m_TempStack));
	}

	template <typename T>
	inline void Push(T value)
	{
		if (sizeof(T) > ArgSize)
		{
			//throw "Argument has an invalid size";
		}
		else if (sizeof(T) < ArgSize)
		{
			// Ensure we don't have any stray data
			*reinterpret_cast<uintptr_t*>(m_TempStack + ArgSize * m_nArgCount) = 0;
		}

		*reinterpret_cast<T*>(m_TempStack + ArgSize * m_nArgCount) = value;
		m_nArgCount++;
	}

	inline void Reverse()
	{
		uintptr_t tempValues[MaxNativeParams];
		uintptr_t* args = (uintptr_t*)m_pArgs;

		for (int i = 0; i < m_nArgCount; i++)
		{
			int target = m_nArgCount - i - 1;

			tempValues[target] = args[i];
		}

		memcpy(m_TempStack, tempValues, sizeof(m_TempStack));
	}

	template <typename T>
	inline T GetResult()
	{
		return *reinterpret_cast<T*>(m_TempStack);
	}
};


class FishNativeContext : public NativeContext
{
public:
	FishNativeContext()
		: NativeContext()
	{

	}

	void Reset()
	{
		m_nArgCount = 0;
		m_nDataCount = 0;
	}

	inline void* GetResultPointer()
	{
		return m_pReturn;
	}
};

struct NativeHash
{
public:
	explicit inline NativeHash(uint64_t hash)
	{
		m_hash = hash;
	}

	inline uint64_t GetHash() const
	{
		return m_hash;
	}

	inline bool operator==(const NativeHash& right) const
	{
		return m_hash == right.m_hash;
	}

	inline bool operator!=(const NativeHash& right) const
	{
		return !(*this == right);
	}

private:
	uint64_t m_hash;
};

namespace std
{
	template<>
	struct hash<NativeHash>
	{
		inline size_t operator()(const NativeHash& hash) const
		{
			return hash.GetHash();
		}
	};
}


static FishNativeContext g_context;
static uint64_t g_hash;

typedef void(__cdecl* NativeHandler)(scrNativeCallContext* context);