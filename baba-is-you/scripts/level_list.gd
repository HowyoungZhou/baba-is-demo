extends ItemList

var levels = [
	# Map
	'Baba Is You', # 00
	'Where Do I Go?', # 01
	'Now What Is This?', # 02
	'Out Of Reach', # 03
	'Still Out Of Reach', # 04
	'Volcano', # 05
	'Off Limits', # 06
	'Grass Yard', # 07
	# The Lake
	'Icy Waters', # 01
	'Turns', # 02
	# 'Affection', # 03
	'Pillar Yard', # 04
	'Brick Wall', # 05
	'Lock', # 06
	'Novice Locksmith', # 07
	'Locked In', # 08
	'Changeless', # 09
	'Two Doors', # 10
	'Jelly Throne', # 11
	# 'Crab Storage', # 12
	'Burglary', # 13
]

# Called when the node enters the scene tree for the first time.
func _ready():
	for level in levels:
		add_item(level)


func _on_level_selected(index):
	var scene_path = 'res://scenes/levels/level_%02d.tscn' % (index + 1)
	get_tree().change_scene(scene_path)
