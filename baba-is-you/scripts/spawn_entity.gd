extends Node

func _on_LevelController_spawn_signals(sprite_type, entity_name, pos_x,pos_y):
	var scene_path = "res://sprites/"+sprite_type+"/"+entity_name.to_lower()+".tscn"
	var scene = load(scene_path)
	var new_entity = scene.instance()
	get_tree().get_current_scene().add_child(new_entity)
	new_entity.set_position(Vector2(12+24*pos_x, 12+24*pos_y))
