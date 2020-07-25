extends MarginContainer

func _on_start_button_pressed():
	get_tree().change_scene('res://scenes/level_list.tscn')


func _on_exit_button_pressed():
	get_tree().quit()
