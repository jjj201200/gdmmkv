extends Node2D


# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	var library_path = "res://a"
	print(ProjectSettings.globalize_path(library_path))
	var mmkv = GDMMKV.new()
	if library_path.begins_with("res://"):
		library_path = ProjectSettings.globalize_path(library_path)

	mmkv.init(library_path, "b.sav")
	prints(mmkv, Time, mmkv.has_store("b.sa"))
	mmkv.set_float("float", 10.1)
	mmkv.set_int("int", 10.1)
	mmkv.set_vector2("vector2", Vector2(1.1, 2.2))
	mmkv.set_vector2i("vector2i", Vector2(1.1, 2.2))
	mmkv.remove_value("vector2");
	#prints(mmkv.get_int("int"), mmkv.get_float("float"), mmkv.get_vector2("vector2"), mmkv.get_vector2("vector2i"), Object.new())
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass
