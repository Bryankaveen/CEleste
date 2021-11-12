#pragma once

#include <cstdint>

struct vec2i {
    int x;
    int y;
};

struct vec2f {
    float x;
    float y;
};

#define NUM_FRUITS 29
#define NUM_CLOUDS 16

struct Cloud {
    float x;
    float y;
    float spd;
    float w;
};

enum type {
    player_spawn = 1,
    platform = 11,
    room_title,
    player,
    big_chest,
    smoke,
    fall_floor,
    fake_wall,
    NUM_TYPES
};

class Object {
public:
    Object(int x, int y);

    bool collideable;
    bool solids;
    float sprite;
    struct {bool x; bool y;} flip;
    float x;
    float y;
    struct {int x; int y; int w; int h;} hitbox;
    uint8_t type;

    int dir; // todo: platform only

    struct vec2f spd;
    struct vec2f rem;

    virtual void update() {}
    virtual void move(float ox, float oy);
    virtual void draw();

    bool is_solid(int ox, int oy);
    bool is_ice(int ox, int oy);
    Object *collide(enum type type, int ox, int oy);
    bool check(enum type type, int ox,int oy);
    void move_x(float amount, float start);
    void move_y(float amount);
};

class Player : public Object {
public:
    bool p_jump;
    bool p_dash;
    int grace;
    int jbuffer;
    int djump;
    int dash_time;
    int dash_effect_time;
    struct vec2f dash_target;
    struct vec2f dash_accel;
    float spr_off;
    bool was_on_ground;

    Player(int x, int y);
    void update() override;
    void draw() override;

    void kill();
};

class PlayerSpawn : public Object {
public:
    struct vec2f target;
    int state;
    int delay;

    PlayerSpawn(int x, int y);
    void update() override;
    void draw() override;
};

class Smoke : public Object {
public:
    Smoke(int x, int y);
    void update() override;
};

class RoomTitle : public Object {
public:
    RoomTitle(int x, int y);
    int delay;

    void draw() override;
};

void _init();
void _update();
void _draw();

void title_screen();
void begin_game();
int level_index();
bool is_title();
void load_room(uint8_t x, uint8_t y);
void restart_room();
void next_room();
Object *init_object(enum type type, int x, int y);
void destroy_object(Object *obj);
void draw_time(int x, int y);
bool solid_at(int x, int y, int w, int h);
bool ice_at(int x, int y, int w, int h);
bool tile_flag_at(int x, int y, int w, int h, uint8_t flag);
uint8_t tile_at(int x, int y);
bool spikes_at(int x, int y, int w, int h, float xspd, float yspd);
float clamp(float val, float a, float b);
float appr(float val, float target, float amount);
int sign(float v);
bool maybe();

extern int freeze;