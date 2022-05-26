#pragma once
#include <graphics/mesh_instance.h>
#include <primitive_builder.h>
#include <box2d/box2d.h>
#include <audio/audio_manager.h>
#include <string>


using std::string;

namespace gef {

	enum class GAMEOBJECTTYPE
	{
		MODEL, OBSTACLE, FIFTY,HUNDRED,NEGONE,FHUNDRED
	};

	class GameObject : public MeshInstance
	{
	public:
		void initialise(b2World* world_, PrimitiveBuilder* primitive_builder_, float x_coord, float y_coord);
		void initialiseHagrid(b2World* world_, PrimitiveBuilder* primitive_builder_, float x_coord, float y_coord, GameObject& objectName, const GAMEOBJECTTYPE& score_value);
		void InitKinematic(b2World* world_, PrimitiveBuilder* primitive_builder_, float x_coord, float y_coord, float x_velo, float  y_velo, GameObject& objectName, const GAMEOBJECTTYPE& score_value);
		void initialiseGround(b2World* world_, PrimitiveBuilder* primitive_builder_, float x_coord, float y_coord, GameObject& objectName, const GAMEOBJECTTYPE& score_value);
		void initialiseScoreCollider(b2World* world_, PrimitiveBuilder* primitive_builder_, float x_coord, float y_coord, float width, GameObject& objectName, const GAMEOBJECTTYPE& score_value);
		void initialiseBoundries(b2World* world_, PrimitiveBuilder* primitive_builder_, float x_coord, float y_coord, float half_height, float half_width, GameObject& objectName, const GAMEOBJECTTYPE& score_value);
		
		void doAudioWhenCollide(AudioManager* audio_manager_, int effect_bonk_, int effect_game_over_, int effect_score_gained_, int effect_life_lost_);
		void updateTransform();
		b2Body* player_body_;
		b2Body* kinematic_body_;
		b2Body* score_body_;	
		
		GameObject* model_;
		GameObject* scorer_pointer;
		GameObject* obstacle_;

		GAMEOBJECTTYPE object_type_;
		
	};

}