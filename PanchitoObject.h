////////////////////////////////////////////////////////////////////////////////
//
// (C) Juanmi Huertas Delgado 2014
//
// 	PanchitoObject represent the runner of the game
//		This class is required by PanchitoJog
//

namespace octet {
	class PanchitoObject{
		//where is Panchito! (this position matches with the bottom of the hat, 
		//						and the top of his body) CENTER of Panchito
		mat4t modelToWorld;

		//First version, Panchito is simple right now! (2 cylinders (hat) + 1 box (body)!)
		float halfWidth;
		float halfHeight;

		//Panchito is easy to draw, he has two colors!
		static vec4 colorHat;
		static vec4 colorBody;
	public:
		PanchitoObject() {
		}

		~PanchitoObject() {
		}

		//This is called to initializate Panchito in a position
		void init(float x, float y, float z){
			//He will have a fixed color, and fix sizes, so we init them
			colorHat = vec4(1,1,1,1); //the hat is black!
			colorBody = vec4(1,0,0,1); //the body is red!!
			halfWidth = 0.5f;
			halfHeight = 0.5f;
			//and now we take x and y (position of Panchito), that can be fixed outside
			modelToWorld.loadIdentity();
			modelToWorld.translate(x, y, z);
		}

		//This method load Panchito to the current scene
		void LoadToScene(ref<visual_scene> scene){
			//First the materials
			material *materialBody = new material(colorBody);
			material *materialHat = new material(colorHat); 
			
			//Then Panchito itself
			//First the body
			mesh_sphere *body = new mesh_sphere(vec3(0,0,0),halfHeight);
			mat4t bodyPosition = modelToWorld;
			bodyPosition.translate(0,-halfWidth*0.5f,0);
			scene_node *nodeBody = new scene_node(bodyPosition,atom_);
			scene->add_child(nodeBody);
			scene->add_mesh_instance(new mesh_instance(nodeBody,body,materialBody));

			//Then the hat (bottom and top)
			mesh_cylinder *hatBottom = new mesh_cylinder(vec3(halfWidth*2,halfHeight*0.1,halfWidth*2));
			mat4t hatBottomPosition = modelToWorld;
			bodyPosition.translate(0,halfWidth*0.05f,0);
			scene_node *nodeHatBottom = new scene_node(hatBottomPosition,atom_);
			scene->add_child(nodeHatBottom);
			scene->add_mesh_instance(new mesh_instance(nodeHatBottom,hatBottom,materialHat));
			
			mesh_cylinder *hatTop = new mesh_cylinder(vec3(halfWidth,halfHeight*0.9,halfWidth));
			mat4t hatTopPosition = modelToWorld;
			bodyPosition.translate(0,halfWidth*0.05f,0);
			scene_node *nodeHatTop = new scene_node(hatTopPosition,atom_);
			scene->add_child(nodeHatBottom);
			scene->add_mesh_instance(new mesh_instance(nodeHatTop,hatTop,materialHat));
		}
	};
}