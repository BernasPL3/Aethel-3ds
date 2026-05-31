extends AnimatedSprite2D

func _process(delta):

	var player = get_parent()

	# PULO
	if not player.is_on_floor():

		play("jump")

	# CORRER
	elif abs(player.velocity.x) > 0:

		play("run")

	# PARADO
	else:

		play("idle")

	# VIRAR SPRITE
	if player.velocity.x > 0:
		flip_h = false

	elif player.velocity.x < 0:
		flip_h = true
