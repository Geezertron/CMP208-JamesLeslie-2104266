#include "GameObject.h"

void gef::GameObject::initialise(b2World* world_, PrimitiveBuilder* primitive_builder_, float x_coord, float y_coord)
{
	// setup the mesh for the player
	set_mesh(primitive_builder_->GetDefaultCubeMesh());

	b2BodyDef player_body_def;
	player_body_def.type = b2_dynamicBody;
	player_body_def.position = b2Vec2(x_coord, y_coord);

	player_body_ = world_->CreateBody(&player_body_def);

	//create a shape for the player physics body
	b2Vec2 vertices[3];
	vertices[0].Set(0.0f, 0.0f);
	vertices[1].Set(1.0f, 0.0f);
	vertices[2].Set(0.0f, 1.0f);
	int32 count = 3;
	b2PolygonShape player_shape;
	player_shape.Set(vertices, count);
	//player_shape.SetAsBox(0.5f, 0.5f);

	//create a fixture for the player
	b2FixtureDef player_fixture_def;
	player_fixture_def.density = 1.f;
	player_fixture_def.restitution = 0.9f;
	player_fixture_def.shape = &player_shape;

	player_body_->CreateFixture(&player_fixture_def);
}


//creates a cube mesh with a kinematic physics body.
//passed  starting position and velocity from scene_app
//also takes instance name and ENUM and sets up user data with regards to how it shhould react in collisions
void gef::GameObject::InitKinematic(b2World* world_, PrimitiveBuilder* primitive_builder_, float x_coord, float y_coord, float x_velo, float  y_velo, GameObject& objectName, const GAMEOBJECTTYPE& score_value)
{
	objectName.object_type_ = score_value;

	b2BodyUserData kinematic_data_;
	kinematic_data_.pointer = (uintptr_t)&objectName;
	//setup mesh for obstacle
	
	set_mesh(primitive_builder_->GetDefaultCubeMesh());

	//create a physics body for the player
	b2BodyDef player_body_def;
	player_body_def.type = b2_kinematicBody;
	player_body_def.userData = kinematic_data_;
	player_body_def.position = b2Vec2(x_coord, y_coord);

	player_body_ = world_->CreateBody(&player_body_def);

	//create the shape for the player
	b2PolygonShape player_shape;
	player_shape.SetAsBox(0.5f, 0.5f);

	//create the fixture
	b2FixtureDef player_fixture_def;
	player_fixture_def.shape = &player_shape;
	player_fixture_def.density = 1.0f;

	player_body_->CreateFixture(&player_fixture_def);

	

	player_body_->SetLinearVelocity(b2Vec2(x_velo, y_velo));
}

//creates a shere mesh with a static physics body. 
// this body is a square turned 45 degrees to make sure the player cannot get stuck on top
//passed  starting position from scene_app
//also takes instance name and ENUM and sets up user data with regards to how it shhould react in collisions
void gef::GameObject::initialiseGround(b2World* world_, PrimitiveBuilder* primitive_builder_, float x_coord, float y_coord, GameObject& objectName, const GAMEOBJECTTYPE& score_value)
{
	objectName.object_type_ = score_value;

	b2BodyUserData ground_data_;
	ground_data_.pointer = (uintptr_t)&objectName;
	// setup the mesh for the player
	//set_mesh(primitive_builder_->GetDefaultCubeMesh());
	set_mesh(primitive_builder_->GetDefaultSphereMesh());

	b2BodyDef player_body_def;
	player_body_def.type = b2_staticBody;
	player_body_def.userData = ground_data_;
	player_body_def.position = b2Vec2(x_coord, y_coord);
	

	player_body_ = world_->CreateBody(&player_body_def);

	//create a shape for the player physics body
	b2Vec2 vertices[4];
	vertices[0].Set(0.f, -0.5f);
	vertices[1].Set(0.5f, -0.25f);
	vertices[2].Set(0.f, 0.5f);
	vertices[3].Set(-0.5f, 0.25f);
	int32 count = 4;
	b2PolygonShape player_shape;
	player_shape.Set(vertices, count);
	//player_shape.SetAsBox(0.5f, 0.5f);
	
	

	//create a fixture for the player
	b2FixtureDef player_fixture_def;
	//player_fixture_def.density = 1.f;
	//player_fixture_def.restitution = 1.0f;
	player_fixture_def.shape = &player_shape;

	player_body_->CreateFixture(&player_fixture_def);
}

//inits hagrid model and correctly offsets the dynamic physics body
//also takes instance name and ENUM and sets up user data with regards to how it shhould react in collisions
void gef::GameObject::initialiseHagrid(b2World* world_, PrimitiveBuilder* primitive_builder_, float x_coord, float y_coord, GameObject& objectName, const GAMEOBJECTTYPE& score_value)
{
	//set up player data for collisions
	
	objectName.object_type_= score_value;
	//model data linked to body
	b2BodyUserData hagrid_data_;
	hagrid_data_.pointer = (uintptr_t)&objectName;
	
	// setup the mesh for the player
	//set_mesh(primitive_builder_->GetDefaultCubeMesh());

	b2BodyDef player_body_def;

	player_body_def.type = b2_dynamicBody;
	player_body_def.position = b2Vec2(x_coord, y_coord);
	player_body_def.userData = hagrid_data_;
	//player_body_def.awake = false;
	player_body_def.awake = true;

	player_body_ = world_->CreateBody(&player_body_def);

	//create a shape for the player physics body
	b2PolygonShape player_shape;
	
	player_shape.SetAsBox(0.4f, 1.0f);


	//create a fixture for the player
	b2FixtureDef player_fixture_def;
	player_fixture_def.density = 1.f;
	player_fixture_def.restitution = 0.5f;
	player_fixture_def.shape = &player_shape;
	

	player_body_->CreateFixture(&player_fixture_def);
	player_body_->SetGravityScale(0);

}


//creates a mesh with  passed height and width and a static physics body. 
// this body is a sensor because it does not need to physically interact with the player
//passed  starting position from scene_app
//also takes instance name and ENUM and sets up user data with regards to how it should react in collisions
void gef::GameObject::initialiseScoreCollider(b2World* world_, PrimitiveBuilder* primitive_builder_, float x_coord, float y_coord,float width, GameObject& objectName, const GAMEOBJECTTYPE& score_value)
{
	//if tatements to find type
	/*if (score_value == GAMEOBJECTTYPE::FIFTY)
	{

	}*/
	//set up player data for collisions
	objectName.object_type_ = score_value;
	//model data linked to body
	b2BodyUserData scorer_data_;
	scorer_data_.pointer = (uintptr_t)&objectName;
	// setup the mesh for the player
	set_mesh(primitive_builder_->GetDefaultCubeMesh());

	b2BodyDef player_body_def;
	player_body_def.type = b2_staticBody;
	player_body_def.position = b2Vec2(x_coord, y_coord);
	player_body_def.userData = scorer_data_;
	

	score_body_ = world_->CreateBody(&player_body_def);

	//create a shape for the player physics body
	b2PolygonShape player_shape;
	player_shape.SetAsBox(width, 0.5f);

	//create a fixture for the player
	b2FixtureDef player_fixture_def;
	player_fixture_def.isSensor = true;
	//player_fixture_def.density = 1.f;
	//player_fixture_def.restitution = 1.0f;
	player_fixture_def.shape = &player_shape;

	score_body_->CreateFixture(&player_fixture_def);
}

//static boundries of the level
//same as ground objects but are passed dimensional data for heigh and width
void gef::GameObject::initialiseBoundries(b2World* world_, PrimitiveBuilder* primitive_builder_, float x_coord, float y_coord, float half_height, float half_width, GameObject& objectName, const GAMEOBJECTTYPE& score_value)
{
	objectName.object_type_ = score_value;

	b2BodyUserData boundry_data_;
	boundry_data_.pointer = (uintptr_t)&objectName;
	//boundary dimensions
	gef::Vector4 boundary_half_demensions(half_height, half_width, 0.5f);

	// setup the mesh for the player

	set_mesh(primitive_builder_->CreateBoxMesh(boundary_half_demensions));
	//set_mesh(primitive_builder_->GetDefaultCubeMesh());

	b2BodyDef player_body_def;
	player_body_def.type = b2_staticBody;
	player_body_def.userData = boundry_data_;
	player_body_def.position = b2Vec2(x_coord, y_coord);

	player_body_ = world_->CreateBody(&player_body_def);

	//create a shape for the player physics body
	b2PolygonShape player_shape;
	player_shape.SetAsBox(half_height, half_width);

	//create a fixture for the player
	b2FixtureDef player_fixture_def;
	//player_fixture_def.density = 1.f;
	//player_fixture_def.restitution = 1.0f;
	player_fixture_def.shape = &player_shape;

	player_body_->CreateFixture(&player_fixture_def);
}

//plays sound effect for all scoring or non-scoring collisions
void gef::GameObject::doAudioWhenCollide(AudioManager* audio_manager_, int effect_bonk_, int effect_game_over_, int effect_score_gained_, int effect_life_lost_)
{
	audio_manager_->PlaySample(effect_bonk_, false);

}

void gef::GameObject::updateTransform()
{
	gef::Matrix44 player_transform;
	player_transform.SetIdentity();

	gef::Matrix44 rotationZ;
	rotationZ.SetIdentity();
	rotationZ.RotationZ(player_body_->GetAngle());

	gef::Matrix44 player_translations;
	player_translations.SetIdentity();
	player_translations.SetTranslation(gef::Vector4(player_body_->GetPosition().x, player_body_->GetPosition().y, 0.0f));


	player_transform = rotationZ * player_translations;
	set_transform(player_transform);
}
