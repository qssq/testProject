/**
 * Created by gongxun on 16/10/9.
 */

var HallMainLayer = GameBaseLayer.extend({
    ctor: function () {
        this._super();
        this.loadCocostudio("hallRes/ccs/HallMain.json");
    }
});