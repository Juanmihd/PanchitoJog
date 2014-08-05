////////////////////////////////////////////////////////////////////////////////
//
// (C) Juanmi Huertas Delgado 2014
//
// 	PanchitoObject represent the runner of the game
//		This class is required by PanchitoJog
//

namespace octet {
	enum {	NUM_MAX_BLOCKS = 4,
			LENGTH_BLOCK = 10,
			WIDTH_BLOCK = 10,
			HEIGTH_BLOCK = 1,
	};
	class terrainBlock{
		//The position where the block is
		mat4t modelToWorld;
		scene_node* blockNode;

		//Terrain has colors (they will have materials, but for now, just color)
		//And we have the ground, and the artifacts attached
		vec4 colorGround;
		vec4 colorArtifacts;

	public:
		terrainBlock(){
			blockNode = 0;
		}

		~terrainBlock(){
			delete blockNode;
		}

		//this is called to create a new terrainBlock from the emptyness
		void init(float x, float z, vec4 colorGround_new, vec4 colorArtifacts_new){
			//First we ad the colors!
			colorGround = colorGround_new;
			colorArtifacts = colorArtifacts_new;
			//and now we get ready the position. Every single terrainBlock will be at height (y) = 0
			modelToWorld.loadIdentity();
			modelToWorld.translate(x,0,z);
			//the node that will hold the block
			if(blockNode = 0)
				blockNode = new scene_node(modelToWorld,atom_);
		}

		void LoadToScene(ref<visual_scene> scene){
			//First the materials
			material *materialGround = new material(colorGround);
			material *materialArtifacts = new material(colorArtifacts);

			//Then the ground (floor)
			mesh_box *ground = new mesh_box(vec3(WIDTH_BLOCK,HEIGTH_BLOCK,LENGTH_BLOCK-1));
			mat4t groundPosition;
			groundPosition.loadIdentity();
			scene_node *nodeGround = new scene_node(groundPosition,atom_);
			blockNode->add_child(nodeGround);
			scene->add_mesh_instance(new mesh_instance(nodeGround,ground,materialGround);
		}

		void runBlock(float distance){
			blockNode->translate(vec3(0,0,distance));
		}

		scene_node * getNode(){
			return blockNode;
		}
	};

	class terrain{
		//The position where the terrain is, this will be fixed
		mat4t modelToWorld;

		//The blocks of the terrain, those will move
		double_list<terrainBlock*> blocks;
		double_list<scene_node*> blockNodes;

		//some variables for blocks "running" effect
		float currentFirstBlockPosition;
		int numberBlocks;

		//Scene for drawing items
		ref<visual_scene> app_scene;

		void add_block(vec4 colorGround, vec4 colorArtifacts){
			terrainBlock * newTerrainBlock;
			newTerrainBlock->init(0,numberBlocks*LENGTH_BLOCK,colorGround,colorArtifacts);
			newTerrainBlock->LoadToScene(app_scene);
			blocks.push_back(newTerrainBlock);
			blockNodes.push_back(newTerrainBlock->getNode());
			++numberBlocks;
		}

		void remove_block(){
			blockNodes.erase(0);
			blocks.erase(0);
		}
	public:
		terrain(){
		}

		~terrain(){
		}

		void LoadToScene(visual_scene * scene){
			app_scene = scene;
		}

		// This will initializate the terrain
		void init(){
			for(int i=0; i<NUM_MAX_BLOCKS; ++i)
				add_block(vec4(1,1,1,1),vec4(0,0,1,1));
			currentFirstBlockPosition = 0;
			numberBlocks = 0;
		}

		// This function will make the ground to "run". 
		// It will take into account the current speed of Panchito
		void run_terrainBlocks(float currentSpeed){
			double_list<terrainBlock*>::iterator it(blocks.begin());
			while(it != blocks.end()){
				(*it)->runBlock(currentSpeed);
				it++;
			}
			currentFirstBlockPosition -= currentSpeed;
			if(currentFirstBlockPosition <= - LENGTH_BLOCK){
				currentFirstBlockPosition = 0;
				remove_block();
				add_block(vec4(1,1,1,1),vec4(0,0,1,1));
			}
		}
	};
}