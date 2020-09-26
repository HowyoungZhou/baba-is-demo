#ifndef BABA_IS_YOU_LEVEL_CONTROLLER_H
#define BABA_IS_YOU_LEVEL_CONTROLLER_H

#include "vector2.h"
#include "words.h"

#include <Godot.hpp>
#include <Node2D.hpp>
#include <InputEvent.hpp>
#include <Control.hpp>

#include <unordered_set>
#include <map>

class Entity;

class LevelController : public godot::Node2D {
GODOT_CLASS(LevelController, godot::Node2D);
public:
    static LevelController *instance;
    std::unordered_set<Entity*> controlled_entities;

    /**
    * Register methods for Godot.
    */
    static void _register_methods() {
        godot::register_method("_enter_tree", &LevelController::_enter_tree);
        godot::register_method("_exit_tree", &LevelController::_exit_tree);
        godot::register_method("_unhandled_input", &LevelController::_unhandled_input);
        godot::register_method("_ready", &LevelController::_ready);
        godot::register_method("_on_viewport_size_changed", &LevelController::_on_viewport_size_changed);

        godot::register_property<LevelController, real_t>("tileSize", &LevelController::set_tile_size,
                                                          &LevelController::get_tile_size, 24.f);
        godot::register_property<LevelController, int>("sceneWidth", &LevelController::set_scene_width,
                                                        &LevelController::get_scene_width, 20);
        godot::register_property<LevelController, int>("sceneHeight", &LevelController::set_scene_height,
                                                        &LevelController::get_scene_height, 18);
        godot::register_signal<LevelController>((char*)"spawn_signals", "sprite_type", GODOT_VARIANT_TYPE_STRING, 
                                                                        "entity_name", GODOT_VARIANT_TYPE_STRING,
                                                                        "pos_x", GODOT_VARIANT_TYPE_VECTOR2,
                                                                        "pos_y", GODOT_VARIANT_TYPE_VECTOR2);
    }

    void _init() {}

    void _ready();

    void _enter_tree() {
        instance = this;
    }

    void _exit_tree() {
        instance = nullptr;
    }

    /**
     * Handle the user input.
     * @param event Input event.
     */
    void _unhandled_input(const godot::Ref<godot::InputEvent> event) {
        if (event->is_action_pressed("ui_up")) move_entities(Vector2<long>(0, -1), Directions::UP);
        else if (event->is_action_pressed("ui_down")) move_entities(Vector2<long>(0, 1), Directions::DOWN);
        else if (event->is_action_pressed("ui_left")) move_entities(Vector2<long>(-1, 0), Directions::LEFT);
        else if (event->is_action_pressed("ui_right")) move_entities(Vector2<long>(1, 0), Directions::RIGHT);
    }

    /**
     * Center the scene when the window size changed.
     */
    void _on_viewport_size_changed() {
        set_position(get_viewport_rect().get_size() / 2 - _tile_size * static_cast<godot::Vector2>(_scene_size) / 2);
    }

    real_t get_tile_size() const {
        return _tile_size;
    }

    void set_tile_size(real_t value) {
        _tile_size = value;
    }

    /**
     * Get the dimension of the tiles.
     * @return Dimension of the tiles.
     */
    Vector2<long> get_tile_dim() {
        auto size = get_viewport_rect().get_size() / _tile_size;
        return Vector2<long>(std::ceil(size.x), std::ceil(size.y));
    }

    /**
     * Set the dimension of the tiles.
     * @param dim New dimention.
     */
    void set_tile_dim(Vector2<long> dim) {
        get_viewport_rect().set_size(static_cast<godot::Vector2>(dim * get_tile_size()));
    }

    void add_controlled_entity(Entity *entity) { controlled_entities.insert(entity); }

    void show_win_screen() {
        cast_to<godot::Control>(get_node("UI/WinScreen"))->set_visible(true);
    }

    void show_lose_screen() {
        cast_to<godot::Control>(get_node("UI/LoseScreen"))->set_visible(true);
    }

    void set_scene_width(int value) {
        _scene_size.x = value;
    }

    int get_scene_width() const {
        return _scene_size.x;
    }

    void set_scene_height(int value) {
        _scene_size.y = value;
    }

    int get_scene_height() const {
        return _scene_size.y;
    }

    void spawn(Nouns object, TilePosition position);

    bool is_win();

private:
    real_t _tile_size = 24.f;
    Vector2<long> _scene_size{20, 18};

    void move_entities(Vector2<long> movement, Directions direction);
};

#endif //BABA_IS_YOU_LEVEL_CONTROLLER_H
