/**
 * Created by gongxun on 16/10/9.
 */

var HelloWorldLayer = cc.Layer.extend({
    sprite:null,
    ctor:function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        /////////////////////////////
        // 2. add a menu item with "X" image, which is clicked to quit the program
        //    you may modify it.
        // ask the window size
        var size = cc.winSize;

        /////////////////////////////
        // 3. add your codes below...
        // add a label shows "Hello World"
        // create and initialize a label
        var helloLabel = new cc.LabelTTF("Hello World", "Arial", 20);
        // position the label on the center of the screen
        helloLabel.x = size.width / 2;
        helloLabel.y = size.height;
        helloLabel.setAnchorPoint(cc.p(0.5, 1));
        // add the label as a child to this layer
        this.addChild(helloLabel, 5);

        helloLabel.setString(this.getSysInfo());

        // add "HelloWorld" splash screen"
        this.sprite = new cc.Sprite("res/HelloWorld.png");
        this.sprite.attr({
            x: size.width / 2,
            y: size.height / 2
        });
        this.addChild(this.sprite, 0);

        //menu
        var item1 = new cc.MenuItemFont("大厅", function(sender){
            cc.log("大厅");
            mo.sceneHelper.runSceneHall();
        });
        item1.setPosition(cc.p(0, 40));

        var menu = new cc.Menu(item1);
        menu.setPosition(cc.p(mo.curSize.x / 2, 0));
        this.addChild(menu);

        return true;
    },

    getSysInfo:function () {
        var result = "";
        result += "语言:";
        result += cc.sys.language;
        result += "\n";

        result += "是否是Native:";
        result += cc.sys.isNative;
        result += "\n";

        result += "是否是手机浏览器:";
        result += cc.sys.isMobile;
        result += "\n";

        result += "浏览器类型:";
        result += cc.sys.browserType;
        result += "\n";

        result += "OS:";
        result += cc.sys.os;
        result += "\n";

        result += "URL:";
        result += cc.openURL;
        result += "\n";

        result += "version:";
        result += cc.sys.version;
        result += "\n";

        return result;
    }
});

var GameScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
        mo.gameScene = this;
    }
});