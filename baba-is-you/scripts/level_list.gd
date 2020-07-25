extends ItemList

var levels = [
	'Baba Is You',
	'Where Do I Go?',
	'Now What Is This?',
	'Out Of Reach',
	'Still Out Of Reach',
	'Volcano',
	'Off Limits',
	'Grass Yard',
	'Slideshow',
	'Fragile Existence',
]

# Called when the node enters the scene tree for the first time.
func _ready():
	for level in levels:
		add_item(level)


func _on_level_selected(index):
	var scene_path = 'res://scenes/levels/level_%02d.tscn' % (index + 1)
	get_tree().change_scene(scene_path)
