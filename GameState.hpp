#pragma once
#include <cstdint>
#pragma pack(push, 8)

class netSyncNodeBase
{
public:
    virtual ~netSyncNodeBase() = default;                                                                                                            // 0x00
    virtual bool IsDataNode() { return false; };                                                                                                     // 0x08
    virtual bool IsParentNode() { return false; };                                                                                                   // 0x10
    virtual void MoveCommonDataOpsVFT() {};                                                                                                          // 0x18
    virtual void ClearChildren() {};                                                                                                                 // 0x20
    virtual void _0x28(void*, void*, void*, int* out_count) {};                                                                                      // 0x28
    virtual bool Serialize(int flags, int flags2, void*, uintptr_t* buffer, int, void*, bool, int*, int* num_serialized) { return false; }  // 0x30
    virtual bool Deserialize(int flags, int flags2, uintptr_t* buffer, void*) { return false; }                                             // 0x38
    virtual int CalculateSize(int flags, int flags2, void*) { return 0; }                                                                            // 0x40
    virtual int CalculateSize2(int flags, int flags2, bool) { return 0; }                                                                            // 0x48

    netSyncNodeBase* m_next_sibling; //0x0008
    netSyncNodeBase* m_prev_sibling; //0x0010
    netSyncNodeBase* m_root; //0x0018
    netSyncNodeBase* m_parent; //0x0020

    uint32_t m_flags1; //0x0028
    uint32_t m_flags2; //0x002C
    uint32_t m_flags3; //0x0030

    uint32_t m_pad2; //0x0034

    netSyncNodeBase* m_first_child; //0x0038
}; //Size: 0x0040
static_assert(sizeof(netSyncNodeBase) == 0x40);
#pragma pack(pop)


#pragma pack(push, 8)
class netSyncDataNode : public netSyncNodeBase
{
public:
    uint32_t flags; //0x40
    uint32_t pad3; //0x44
    uint64_t pad4; //0x48

    netSyncDataNode* parentData; //0x50
    uint32_t childCount; //0x58
    netSyncDataNode* children[8]; //0x5C
    uint8_t syncFrequencies[8]; //0x9C
    void* commonDataOpsVFT; //0xA8 wtf
};
static_assert(sizeof(netSyncDataNode) == 0xB0);
#pragma pack(pop)

class NodeCommonDataOperations
{
public:
    virtual ~NodeCommonDataOperations() = default;
    virtual void ReadFromBuffer(netSyncDataNode* node) {};            // 0x08
    virtual void WriteToBuffer(netSyncDataNode* node) {};             // 0x10
    virtual void Unk() {};                                                  // 0x18
    virtual int CalculateSize(netSyncDataNode* node) { return 0; };   // 0x20
    virtual int CalculateSize2(netSyncDataNode* node) { return 0; };  // 0x28
    virtual void LogSyncData(netSyncDataNode* node) {};               // 0x30
    virtual void LogSyncData2(netSyncDataNode* node) {};              // 0x38

    uintptr_t* m_buffer; // 0x8
};
static_assert(sizeof(NodeCommonDataOperations) == 0x10);

class CProjectBaseSyncDataNode : public netSyncDataNode
{
public:
    virtual bool IsSyncNode() { return false; }                                 // 0x50
    virtual bool _0x58() { return false; }                                      // 0x58
    virtual bool IsGlobalFlags() { return false; }                              // 0x60
    virtual void DoPreCache(uintptr_t* data) {}                         // 0x68
    virtual std::uint8_t GetSyncFrequency(int index) { return 0; }              // 0x70
    virtual int GetSyncInterval(int index) { return 0; }                        // 0x78
    virtual int GetBandwidthForPlayer(int player) { return 200; }               // 0x80 (should always return 200)
    virtual void _0x88(void*) {}                                                // 0x88
    virtual bool _0x90(void*, void*, int, int, int) { return false; }           // 0x90
    virtual int CalculateSize() { return 0; }                                   // 0x98 need to verify later
    virtual bool IsPreCacheDisabled() { return false; }                         // 0xA0
    virtual bool CanApply(uintptr_t* object) { return false; }            // 0xA8
    virtual int GetPlayersInScope() { return -1; }                              // 0xB0
    virtual void DeserializeImpl() {}                                           // 0xB8 need to verify later
    virtual void SerializeImpl() {}                                             // 0xC0 need to verify later
    virtual int CalculateSize2() { return 0; }                                  // 0xC8
    virtual int _0xD0() { return 0; }                                           // 0xD0 calls NodeCommonDataOperations::Unk()
    virtual void Log() {}                                                       // 0xD8
    virtual bool CanPreCache(int) { return false; }                             // 0xE0 arg is always zero afaik
    virtual bool CanBeEmpty() { return false; }                                 // 0xE8
    virtual bool IsEmpty() { return false; }                                    // 0xF0 returns true if all data is default
    virtual void SetEmpty() {}                                                  // 0xF8 sets all data to their default values
    virtual void Log2() {}                                                      // 0x100
    virtual void ResetScriptData() {}                                           // 0x108
    virtual bool _0x110() { return false; }                                     // 0x110

private:
    NodeCommonDataOperations m_common_data_operations; // 0xB0 this is generally invalidated by MoveCommonDataOpsVFT()
};
//static_assert(sizeof(CProjectBaseSyncDataNode) == 0xC0);
class CSyncDataNodeFrequent : public CProjectBaseSyncDataNode {};
class CSyncDataNodeInfrequent : public CProjectBaseSyncDataNode {};



#pragma pack(push,4)
class CPlayerGameStateDataNode : CSyncDataNodeInfrequent
{
public:
    uint32_t m_player_state; //0x00C0
    bool m_controls_disabled_by_script; //0x00C4
    bool m_is_max_armor_and_health_default; //0x00C5
    bool unk_000C6; //0x00C6
    bool m_is_spectating; //0x00C7
    bool m_is_antagonistic_to_another_player; //0x00C8
    bool m_never_target; //0x00C9
    bool m_use_kinematic_physics; //0x00CA
    bool m_has_tutorial_data; //0x00CB
    bool m_pending_tutorial_change; //0x00CC
    bool unk_00CD; //0x00CD
    bool m_respawning; //0x00CE
    bool m_will_jack_any_player; //0x00CF
    bool m_will_jack_wanted_players; //0x00D0
    bool m_dont_drag_from_car; //0x00D1
    bool m_random_peds_flee; //0x00D2
    bool m_every_ped_back_away; //0x00D3
    bool m_has_microphone; //0x00D4
    bool m_is_invincible; //0x00D5
    bool unk_00D6; //0x00D6
    bool unk_00D7; //0x00D7
    bool m_seatbelt; //0x00D8
    bool unk_00D9; //0x00D9
    bool m_bullet_proof; //0x00DA
    bool m_fire_proof; //0x00DB
    bool m_explosion_proof; //0x00DC
    bool m_collision_proof; //0x00DD
    bool m_melee_proof; //0x00DE
    bool m_water_proof; //0x00DF
    bool m_steam_proof; //0x00E0
    bool unk_00E1; //0x00E1
    bool unk_00E2; //0x00E2
    bool unk_00E3; //0x00E3
    bool unk_00E4; //0x00E4
    bool unk_00E5; //0x00E5
    bool unk_00E6; //0x00E6
    bool unk_00E7; //0x00E7
    bool unk_00E8; //0x00E8
    bool unk_00E9; //0x00E9
    bool unk_00EA; //0x00EA
    bool unk_00EB; //0x00EB
    bool unk_00EC; //0x00EC
    bool unk_00ED; //0x00ED
    bool unk_00EE; //0x00EE
    bool unk_00EF; //0x00EF
    bool unk_00F0; //0x00F0
    bool unk_00F1; //0x00F1
    bool unk_00F2; //0x00F2
    bool unk_00F3; //0x00F3
    bool unk_00F4; //0x00F4
    bool unk_00F5; //0x00F5
    bool unk_00F6; //0x00F6
    bool unk_00F7; //0x00F7
    bool unk_00F8; //0x00F8
    bool unk_00F9; //0x00F9
    bool unk_00FA; //0x00FA
    bool unk_00FB; //0x00FB
    uint32_t unk_00FC; //0x00FC
    uint32_t m_mobile_ring_state; //0x0100
    int32_t m_player_team; //0x0104
    float m_air_drag_multiplier; //0x0108
    uint32_t m_max_health; //0x010C
    uint32_t m_max_armor; //0x0110
    uint32_t m_jack_speed; //0x0114
    uint16_t m_player_is_targetable_by_team; //0x0118
    uint32_t m_override_receive_chat; //0x011C
    uint32_t m_override_send_chat; //0x0120
    bool unk_0124; //0x0124
    bool unk_0125; //0x0125
    bool unk_0126; //0x0126
    bool unk_0127; //0x0127
    uint16_t m_spectating_net_id; //0x0128
    uint8_t m_antagonistic_to_player_id; //0x012C
    uint8_t m_tutorial_index; //0x012B
    uint8_t m_tutorial_instance_id; //0x012C
    char pad_012D[2]; //0x012D
    float m_microphone_volume; //0x0130
    uint32_t m_voice_channel; //0x0134
    bool m_is_overriding_voice_proximity; //0x0138
    char pad_0139[7]; //0x0139
    float m_voice_proximity_x; //0x0140
    float m_voice_proximity_y; //0x0144
    float m_voice_proximity_z; //0x0148
    float m_voice_proximity_radius_maybe; //0x014C
    uint32_t unk_0150; //0x0150
    uint32_t m_vehicle_weapon_index; //0x0154
    bool m_has_vehicle_weapon_index; //0x0158
    uint32_t m_decor_count; //0x015C
    uint32_t m_decor_type[3]; // 0x0160
    uint32_t m_decor_value[3]; // 0x016C
    uint32_t m_decor_name_hash[3]; // 0x0178
    bool m_friendly_fire_allowed; //0x0184
    bool unk_0185; //0x0185
    uint8_t m_current_garage_instance_index; //0x0186
    uint8_t m_current_property_id; //0x0187
    uint8_t unk_0188; //0x0188
    uint8_t unk_0189; //0x0189
    bool m_battle_aware; //0x018A
    bool m_vehicle_jump_down; //0x018B
    float m_weapon_defence_modifier; //0x018C
    float m_weapon_defence_modifier_2; //0x0190
    bool m_is_overriding_population_control_sphere; //0x0194
    char pad_0195[11]; //0x0195
    float m_population_control_sphere_x; //0x01A0
    float m_population_control_sphere_y; //0x01A4
    float m_population_control_sphere_z; //0x01A8
    uint16_t unk_01AC; //0x01AC
    uint16_t unk_01AE; //0x01AE
    uint16_t unk_01B0; //0x01B0
    bool pad_01B2; //0x01B2
    bool unk_01B3; //0x01B3
    bool m_no_collision; //0x01B4
    bool unk_01B5; //0x01B5
    bool unk_01B6; //0x01B6
    bool m_super_jump; //0x01B7
    bool unk_01B8; //0x01B8
    bool unk_01B9; //0x01B9
    uint16_t unk_01BA; //0x01BA
    uint32_t unk_01BC; //0x01BC
    float unk_01C0; //0x01C0
    float m_weapon_damage_modifier;  //0x01C4 Divisor: 0x3F800000
    float m_melee_weapon_damage_modifier;  //0x01C8 Divisor: 0x3F800000
    float unk_01CC; //0x01CC
    bool unk_01D0; //0x01D0
    char pad_01D1[15]; //0x01D1
    float unk_01E0; //0x01E0
    float unk_01E4; //0x01E4
    float unk_01E8; //0x01E8
    uint32_t unk_01EC; //0x01EC
    uint8_t unk_01F0; //0x01F0
    uint8_t unk_01F1; //0x01F1
    bool unk_01F2; //0x01F2
    uint8_t unk_01F3; //0x01F3
    bool unk_01F4; //0x01F4
    bool unk_01F5; //0x01F5
}; //Size: 0x01F8
//static_assert(sizeof(CPlayerGameStateDataNode) == 0x1F8);
#pragma pack(pop)