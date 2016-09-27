#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <string>
#include <vector>

using namespace std;
USING_NS_CC;

vector<string>& split( const string& ori , char ch , vector<string>& ans )
{
    istringstream iss(ori);
    string item;
    while(getline(iss , item , ch)) ans.push_back(item);
    return ans;
}

vector<string> split( const string& ori , char ch )
{
    vector<string> ans;
    split(ori , ch , ans);
    return ans;
}


Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
//    this->addChild(sprite, 0);
    
    ssize_t size;
    char* pBuffer = (char*)FileUtils::getInstance()->getFileData(FileUtils::getInstance()->fullPathForFilename("test01.txt").c_str(), "rt", &size);
    string temp(pBuffer, size);
    stringstream ss;
    ss<<temp;
    string it;
    string zifu = "\r\t";
    //CLogHelper::singleton()->Log("ø™ º");
    vector<Point> ps;
    while (getline(ss, it))
    {
        //CLogHelper::singleton()->Log(it);
        vector<string> pos = split(it, ',');
        int p1 = __String::createWithFormat("%s", pos[0].c_str())->intValue();
        int p2 = __String::createWithFormat("%s", pos[1].c_str())->intValue();
        ps.push_back(Point(p1, p2));
    }
    
    static int index = 0;
    Sprite *test = Sprite::create("CloseSelected.png");
    this->addChild(test);
    this->schedule([=](float dt){
        test->setPosition(ps[index]);
        index++;
        if (index >= ps.size())
        {
            index = 0;
        }
    }, 20.0f / 1000.0f, "fishPath");
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
