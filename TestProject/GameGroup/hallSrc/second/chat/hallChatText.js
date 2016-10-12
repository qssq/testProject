/**
 * Created by gongxun on 16/10/10.
 */

var HallChatText = ccui.Layout.extend({
    mChatBg : null,
    mChatHead : null,
    mRichText : null,

    //上下留白
    mLayotHeightOffset : null,

    //richtext实际大小
    mRichTextRealSize : null,

    //richtext坐标
    mRichTextRealPos : null,

    ctor: function (isMy, text) {
        this._super();

        this.mLayotHeightOffset = 40;

        //设置richtext
        this.setRichTextElment(text);
        this.setRichTextPos(isMy, text);

        //容器大小
        this.setContentSize(mo.curSize.x, this.mLayotHeightOffset * 2 + this.mRichTextRealSize.height);

        //head
        this.mChatHead = new cc.Sprite("hallRes/ccs/chat/common_male_head@2x.png");
        this.mChatHead.setPosition(cc.p(isMy ? mo.curSize.x - 60 : 60, this.mLayotHeightOffset + this.mRichTextRealSize.height));
        this.mChatHead.setScale(0.4);
        this.addChild(this.mChatHead);

        //chat bg
        var addSize = cc.size(60, 30);
        this.mChatBg = new cc.Scale9Sprite(isMy ? "hallRes/ccs/chat/chatroom_my_msg@2x.png" : "hallRes/ccs/chat/chatroom_friend_item_bg_pressed@2x.png", cc.rect(0, 0, 100, 82), cc.rect(30, 30, 40, 22));
        this.mChatBg.setAnchorPoint(cc.p(0.5, 1));
        this.mChatBg.setContentSize(cc.size(this.mRichTextRealSize.width + addSize.width, this.mRichTextRealSize.height + addSize.height));
        this.mChatBg.setPosition(cc.p(this.mRichTextRealPos.x, this.mRichTextRealPos.y + addSize.height / 2));
        this.addChild(this.mChatBg, 1);
    },

    //设置RichText 大小
    setRichTextPos : function(isMy, text){
        var maxWidth = 400;
        var offsetX = 140;

        this.mRichText.ignoreContentAdaptWithSize(true);
        this.mRichText.formatText();

        var virtualRendererSize = this.mRichText.getVirtualRendererSize();
        var oneColWidth = virtualRendererSize.width;
        var onColAddX = 0;

        var realHeight = virtualRendererSize.height;
        var realWidth = virtualRendererSize.width;

        //1richText自动换行后取不到实际宽度
        //2richText没有自动换行时候 anchorPos:(0.5, 0.5) 自动换行后anchorPos:(0.5, 1);
        if (oneColWidth > maxWidth){
            realWidth = maxWidth;

            this.mRichText.ignoreContentAdaptWithSize(false);
            this.mRichText.setContentSize(cc.size(maxWidth, 0));
            if (cc.sys.isNative){
                this.mRichText.setWrapMode(1);
            }
            this.mRichText.formatText();
            realHeight = this.mRichText.getNewContentSizeHeight();
        } else {
            if (!cc.sys.isNative){
                onColAddX = realHeight / 2;
            }
        }

        this.mRichText.setAnchorPoint(cc.p(0.5, 1));
        this.mRichText.setPosition(cc.p(isMy ? mo.curSize.x - offsetX - realWidth / 2 : offsetX + realWidth / 2, this.mLayotHeightOffset + virtualRendererSize.height / 2 + onColAddX + realHeight));

        //设置成员变量
        this.mRichTextRealSize = cc.size(realWidth, realHeight);
        this.mRichTextRealPos = cc.p(cc.p(isMy ? mo.curSize.x - offsetX - realWidth / 2 : offsetX + realWidth / 2, this.mLayotHeightOffset + virtualRendererSize.height / 2 + realHeight))
    },

    setRichTextElment : function(text){
        this.mRichText = new ccui.RichText();
        this.addChild(this.mRichText, 2);

        var imageArray = new Array();
        for(var i = 0; i < text.length; i++){
            if (text.charAt(i) == '['){
                if (text.length - i >= 5 &&
                    text.substring(i, i + 2) == "[e" &&
                    text.charAt(i + 4) == "]"
                ){
                    imageArray.push(i);
                }
            }
        }

        for(var i = 0; i < imageArray.length; i++){
            var lastIndex = i == 0 ? 0 : imageArray[i - 1] + 5;

            var temp = text.substring(lastIndex, imageArray[i]);
            if (temp != ""){
                var reText = new ccui.RichElementText(1, cc.color.BLACK, 255, temp, "", 28);
                this.mRichText.pushBackElement(reText);
            }

            var numStr = text.substring(imageArray[i] + 2, imageArray[i] + 4);
            var num = parseInt(numStr);
            if (num >=0 && num <= 6){
                var reImg = new ccui.RichElementImage(2, cc.color.WHITE, 255, "hallRes/ccs/chat/chat_face_" + num + ".png");
                this.mRichText.pushBackElement(reImg);
            }
        }

        var startIndex = imageArray.length == 0 ? 0 : imageArray[imageArray.length - 1] + 5;
        var lastTemp = text.substring(startIndex, text.length);
        if (lastTemp != ""){
            var reText = new ccui.RichElementText(1, cc.color.BLACK, 255, lastTemp, "", 28);
            this.mRichText.pushBackElement(reText);
        }

    }
});