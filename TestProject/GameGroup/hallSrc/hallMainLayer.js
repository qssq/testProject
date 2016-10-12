/**
 * Created by gongxun on 16/10/9.
 */

var HallMainLayer = GameBaseLayer.extend({
    mTabArray : null,
    mTabBtns : null,
    ctor: function () {
        this._super();
        this.loadCocostudio("hallRes/ccs/HallMain.json");

        this.loadTab();

        mo.hallDefines.hallMainlLayer = this;
    },
    onEnter : function(){
        this._super();
        this.intoTabIndex(1);
    },

    loadTab : function(){
        //tab item
        this.mTabArray = new Array();

        var msgLayer = new HallMsgLayer();
        ccui.helper.seekWidgetByName(this.ccsNode, "Panel_content").addChild(msgLayer);
        this.mTabArray.push(msgLayer);

        var fastLayer = new HallFastLayer();
        ccui.helper.seekWidgetByName(this.ccsNode, "Panel_content").addChild(fastLayer);
        this.mTabArray.push(fastLayer);

        //tab button
        this.mTabBtns = new Array();

        var Image_xiaoxi = ccui.helper.seekWidgetByName(this.ccsNode, "Image_xiaoxi");
        this.mTabBtns.push(Image_xiaoxi);

        var Image_zhong = ccui.helper.seekWidgetByName(this.ccsNode, "Image_zhong");
        this.mTabBtns.push(Image_zhong);

        for(var i = 0; i < this.mTabBtns.length; i++){
            this.mTabBtns[i].addTouchEventListener(function(sender, type){
                if (type == ccui.Widget.TOUCH_ENDED) {
                    this.intoTabIndex(sender.getTag());
                }
            }, this);
        }
    },

    intoTabIndex : function(index){
        for(var i = 0; i < 2; i++){
            this.mTabArray[i].setVisible(i == index);
        }
    }
});