/**
 * Created by gongxun on 16/10/9.
 */

var SceneHlper = function(){
    var that = [];

    that.init = function(){
        //加载通用js
        cc.loader.loadJs(["src/files.js"], function(err){
            cc.loader.loadJs(Files, function(err){
                that.runSceneTest();
            });
        });
    };

    that.runSceneTest = function() {
        cc.LoaderScene.preload(Resource, function () {
            //cc.director.runScene(new GameScene());
            that.runSceneHall();
        }, this);
    };

    that.runSceneHall = function () {
        cc.loader.loadJs(["hallSrc/files.js"], function (err) {
            cc.loader.loadJs(Files, function (err) {
                cc.LoaderScene.preload(Resource, function () {
                    cc.director.runScene(new HallScene());
                }, this);
            });
        });
    };

    return that;
};

mo.gameScene = null;
mo.sceneHelper = new SceneHlper();