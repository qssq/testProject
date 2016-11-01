/**
 * Created by gongxun on 16/10/9.
 */

var HallFastLayer = GameBaseLayer.extend({
    ctor: function () {
        this._super();
        this.loadCocostudio("hallRes/ccs/HallFastLayer.json");

        ccui.helper.seekWidgetByName(this.ccsNode, "ListView_content").setScrollBarEnabled(false);

        //this._box1 = new cc.EditBox(cc.size(170, 50), new cc.Scale9Sprite("hallRes/green_edit.png"), new cc.Scale9Sprite("hallRes/orange_edit.png"));
        //this._box1.setString("EditBoxs");
        //this._box1.x = mo.curSize.x / 2;
        //this._box1.y = 300;
        //this._box1.setFontColor(cc.color(251, 250, 0));
        //this.addChild(this._box1);
    }
});