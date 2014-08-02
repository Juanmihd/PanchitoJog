////////////////////////////////////////////////////////////////////////////////
//
// (C) Juanmi Huertas Delgado 2014
//
// 	PanchitoObject represent the runner of the game
//		This class is required by PanchitoJog
//

namespace octet {
	class terrainBlock{
		//The position where the block is
		scene_node* blockNode;

	public:
		terrainBlock(){
			blockNode = 0;
		}

		~terrainBlock(){
			delete blockNode;
		}
	};

	class terrain{
		//The position where the terrain is, this will be fixed
		mat4t modelToWorld;

		//The blocks of the terrain, those will move
		dynarray<terrainBlock*> blocks;
		dynarray<scene_node*> blockNodes;

	public:
		terrain(){

		}

		~terrain(){

		}
	};
}