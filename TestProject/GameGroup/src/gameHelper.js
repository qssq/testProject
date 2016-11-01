/**
 * Created by gongxun on 16/10/17.
 */

var GameHelper = function(){
    var that = [];

    that.setTextString = function(text, content){
        text.setString(content);
        text.setContentSize(text.getAutoRenderSize());
    };

    return that;
};

mo.gameHelper = new GameHelper();