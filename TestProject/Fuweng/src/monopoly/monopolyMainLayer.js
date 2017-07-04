/**
 * Created by gongxun on 17/2/3.
 */

var MonopolyMainLayer = cc.Layer.extend({
    mMoveLayer : null,
    mTilemapLayer : null,
    mMonopolyHudLayer : null,
    mPlayers : null,
    mPlayerLayer : null,

    mIsCameraMove : null,
    ctor : function(){
        this._super();

        mo.monopoly = this;

        //初始化
        mo.monopolyHelper.init();
        this.mIsCameraMove = true;

        //层
        this.mMoveLayer = new cc.Layer();
        this.addChild(this.mMoveLayer);

        this.mTilemapLayer = new TilemapLayer();
        this.mMoveLayer.addChild(this.mTilemapLayer);

        this.mPlayerLayer = new PlayerLayer();
        this.mMoveLayer.addChild(this.mPlayerLayer);

        this.mMonopolyHudLayer = new MonopolyHudLayer();
        this.addChild(this.mMonopolyHudLayer);
    },

    onEnter : function(){
        this._super();

        this.loadTouch();
    },

    onExit : function(){
        this._super();
    },

    loadTouch : function(){
        var that = this;

        cc.eventManager.addListener({
            event: cc.EventListener.TOUCH_ALL_AT_ONCE,
            onTouchesBegan : function(touches, event){
                return that.mIsCameraMove;
            },
            onTouchesMoved : function (touches, event) {
                var touch = touches[0];
                var delta = touch.getDelta();

                that.mMoveLayer.x += delta.x;
                that.mMoveLayer.y += delta.y;
            }
        }, this);
    },

    //移动
    playerMove : function(seat, from, to, dis){
        this.mMonopolyHudLayer.setMyControl(false);

        this.mPlayerLayer.move(from, to, dis);

        this.setCameraMove(true);
    },

    //移动完毕
    playerMoveEnd : function(){
        this.mMonopolyHudLayer.setMyControl(true);

        this.setCameraMove(false);
    },

    //设置摄像机镜头
    setCameraMove : function(isShow){
        this.mIsCameraMove = !isShow;

        if (isShow){
            this.unschedule(this.updateCameraMove);
            this.schedule(this.updateCameraMove);
        }else{
            this.unschedule(this.updateCameraMove);
        }
    },

    //更新摄像头
    updateCameraMove : function(dt){
        var playerPos = this.mPlayerLayer.mPlayerSprite.getPosition();
        this.mMoveLayer.x = -(playerPos.x - mo.curSize.x / 2);
        this.mMoveLayer.y = -(playerPos.y - mo.curSize.y / 2);
    }
});