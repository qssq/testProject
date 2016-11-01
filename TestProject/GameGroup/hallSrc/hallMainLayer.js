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
        this.intoTabIndex(2);
    },

    loadTab : function(){
        //tab item
        this.mTabArray = new Array();

        var clubListLayer = new HallCLubListLayer();
        ccui.helper.seekWidgetByName(this.ccsNode, "Panel_content").addChild(clubListLayer);
        this.mTabArray.push(clubListLayer);

        var msgLayer = new HallMsgLayer();
        ccui.helper.seekWidgetByName(this.ccsNode, "Panel_content").addChild(msgLayer);
        this.mTabArray.push(msgLayer);

        var fastLayer = new HallFastLayer();
        ccui.helper.seekWidgetByName(this.ccsNode, "Panel_content").addChild(fastLayer);
        this.mTabArray.push(fastLayer);

        //tab button
        this.mTabBtns = new Array();

        var Image_faxian = ccui.helper.seekWidgetByName(this.ccsNode, "Image_faxian");
        this.mTabBtns.push(Image_faxian);

        var Image_xiaoxi = ccui.helper.seekWidgetByName(this.ccsNode, "Image_xiaoxi");
        this.mTabBtns.push(Image_xiaoxi);

        var Image_zhong = ccui.helper.seekWidgetByName(this.ccsNode, "Image_zhong");
        this.mTabBtns.push(Image_zhong);

        for(var i = 0; i < this.mTabBtns.length; i++) {
            this.mTabBtns[i].addTouchEventListener(function (sender, type) {
                if (type == ccui.Widget.TOUCH_ENDED) {
                    this.intoTabIndex(sender.getTag());
                }
            }, this);
        }
    },

    intoTabIndex : function(index){
        var normalFiles = [
            "hallRes/ccs/hall/tab_discovery@2x.png",
            "hallRes/ccs/hall/tab_moments@2x.png",
            "hallRes/ccs/hall/tab_game_pressed@2x.png"
        ];

        var selcetFiles = [
            "hallRes/ccs/hall/tab_discovery_pressed@2x.png",
            "hallRes/ccs/hall/tab_moments_pressed@2x.png",
            "hallRes/ccs/hall/tab_game@2x.png"
        ];

        for(var i = 0; i < 3; i++){
            this.mTabArray[i].setVisible(i == index);
            this.mTabBtns[i].loadTexture(i == index ? selcetFiles[i] : normalFiles[i]);
        }
    }
});