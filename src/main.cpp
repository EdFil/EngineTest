struct SimpleClass {
    SimpleClass() { printf("SimpleClass Constructor\n"); }
    SimpleClass(const SimpleClass&) { printf("SimpleClass Copy Constructor\n"); }
    SimpleClass(SimpleClass&&) noexcept { printf("SimpleClass Move Constructor\n"); }
    ~SimpleClass() { printf("SimpleClass Destructor\n"); }

    SimpleClass& operator=(const SimpleClass&) { printf("SimpleClass Copy Assignment Operator\n"); return *this; }
    SimpleClass& operator=(SimpleClass&&) noexcept { printf("SimpleClass Move Assignment Operator\n"); return *this; }

    int i;
};

int main() {
    ObjectPool<SimpleClass> pool;

    const size_t numHandles = 5;
    pool.initWithSize(numHandles);
    ObjectPoolHandle handles[numHandles];
    for (size_t i = 0; i < numHandles; i++) {
        handles[i] = pool.getNewHandle();
        pool[handles[i]].i = 100 * i;
    }

    pool.releaseHandle(handles[2]);
    pool.releaseHandle(handles[3]);
    ObjectPoolHandle handle2 = pool.getNewHandle();
    pool[handles[handle2]].i = 2000;
    ObjectPoolHandle handle3 = pool.getNewHandle();
    pool[handles[handle3]].i = 3000;
    return 0;
}


//#include <Engine.hpp>
//#include <Constants.hpp>
//#include <file/FileManager.hpp>
//#include <SDL_log.h>
//#include <scene/Scene.hpp>
//#include <TextureManager.hpp>
//
//#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image.h>
//
//#include <string>
//#include <ctime>
//
//class MyScene : public Scene {
//	static const int k_numNodes = 7000;
//	Node* _nodes[k_numNodes] = {};
//
//	void onCreated() override {
//		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "My onCreate()");
//
//		SDL_Texture* texture = _engine->textureManager()->loadTexture("AnotherImage.png");
//
//		for (int i = 0; i < k_numNodes; i++) {
//
//			Node* node = new Node();
//
//			const GlobalHandle transformComponentHandle = _engine->transformSystem().create();
//			node->addComponentHandle(transformComponentHandle);
//
//			const GlobalHandle spriteComponentHandle = _engine->spriteSystem().createComponent(transformComponentHandle, texture);
//			node->addComponentHandle(spriteComponentHandle);
//
//			const GlobalHandle randomMovementHandle = _engine->randomMovementSystem().createComponent(transformComponentHandle, spriteComponentHandle);
//			node->addComponentHandle(randomMovementHandle);
//
//			_nodes[i] = node;
//		}
//	}
//
//	void onDestroy() override {
//		for (int i = 0; i < k_numNodes; i++) {
//			delete _nodes[i];
//		}
//		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "My onDestroy()");
//	}
//};
//
//int main()
//{
//	srand(time(nullptr));
//
//	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
//
//    FileManager::initialize();
//
//	//std::string fullPath = FileManager::instance()->fullPathForFile("ImageTest->png");
//	//std::vector<char> data = FileManager::instance()->loadFile("ImageTest->png");
//
//    //int x, y, channels_in_file;
//    //stbi_uc* result = stbi_load(fullPath->c_str(), &x, &y, &channels_in_file, 4);
//    //stbi_image_free(result);
//
//
//    Engine* engine = new Engine();
//    if(engine->initialize()) {
//		engine->setScene(std::make_unique<MyScene>());
//        engine->run();
//    }
//
//    return 0;
//}