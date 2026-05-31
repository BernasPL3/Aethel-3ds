extends CharacterBody2D

# CONFIG
const SPEED = 220.0
const JUMP_FORCE = -420.0
const GRAVITY = 900.0

# SPRITE
@onready var anim = $AnimatedSprite2D

func _physics_process(delta):

	# Gravidade
	if not is_on_floor():
		velocity.y += GRAVITY * delta

	# Pulo
	if Input.is_action_just_pressed("ui_accept") and is_on_floor():
		velocity.y = JUMP_FORCE

	# Movimento
	var direction = Input.get_axis("ui_left", "ui_right")

	if direction:
		velocity.x = direction * SPEED
	else:
		velocity.x = 0

	# Virar personagem
	if direction > 0:
		anim.flip_h = false

	elif direction < 0:
		anim.flip_h = true

	# ANIMAÇÕES
	if not is_on_floor():

		if anim.animation != "jump":
			anim.play("jump")

	elif direction != 0:

		if anim.animation != "run":
			anim.play("run")

	else:

		if anim.animation != "idle":
			anim.play("idle")

	# Aplicar movimento
	move_and_slide()
