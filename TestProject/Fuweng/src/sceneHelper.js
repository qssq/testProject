/**
 * Created by gongxun on 16/11/18.
 */


var SceneHlper = function(){
    var that = [];


    that.init = function(){
        //初始化
        if (cc.sys.isNative){
            cc.log("write path:" + jsb.fileUtils.getWritablePath());
        }

        that.start();
    };

    that.start = function(){
        //加载通用js
        cc.loader.loadJs(["src/files.js"], function(err){
            cc.loader.loadJs(Files, function(err){
                cc.LoaderScene.preload(Resource, function () {
                    cc.director.runScene(new MainScene());
                    that.intoChessLayer();
                }, this);
            });
        });
    };

    that.intoMainLayer = function () {
        mo.mainScene.removeAllChildren();

        mo.mainScene.addChild(new MonopolyMainLayer());
    };

    that.intoLoginLayer = function(){
        mo.mainScene.removeAllChildren();

        mo.mainScene.addChild(new LoginLayer());
    };

    that.intoSnakeLayer = function(){
        mo.mainScene.removeAllChildren();

        mo.mainScene.addChild(new SnakeMainLayer());
    };

    that.intoChessLayer = function(){
        mo.mainScene.removeAllChildren();

        mo.mainScene.addChild(new ChessTableLayer());
    };

    return that;
};

//主界面
mo.mainScene = null;

mo.sceneHelper = new SceneHlper();