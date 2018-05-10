package main

import (
	"strings"
	"encoding/xml"
	"strconv"
	"fmt"
)

func main() {
	//Feedesc := "0.01￥"
	//score, _ := strconv.ParseFloat(strings.Replace(Feedesc, "￥", "", -1), 64)
	//money := int(score * 1000)
	//fmt.Printf("monry:%d\n", money)
	//
	//body := "{\"error\":207,\"data\":{\"errMsg\":\"\u7528\u6237\u4e0d\u5b58\u5728\"}}"
	//type HtmlBody struct {
	//	Error int64 `json:"error"`
	//}
	//
	//content := []byte(body)
	//htmlBody := HtmlBody{}
	//err := json.Unmarshal(content, &htmlBody)
	//if err != nil {
	//	fmt.Println("-1")
	//	panic(err.Error())
	//}
	//
	//if htmlBody.Error == 0 {
	//	fmt.Println("0")
	//} else if htmlBody.Error == 207 {
	//	fmt.Println("2")
	//} else if htmlBody.Error == 235 {
	//	fmt.Println("1")
	//} else {
	//	fmt.Println("-1")
	//}
	//
	//num, err := strconv.Atoi("")
	//fmt.Println(num)
	//numstr := strconv.Itoa(num)
	//fmt.Println(numstr)


	//xmlData := "&lt;msg fromusername=\"wxid_d7r5zm3n1m0d21\" encryptusername=\"v1_ccfae92d5d10c275764b317870c988a7bce10cba21996a18983111e0916216571cbdc88206af6ec2ef88b5b4aee733b0@stranger\" fromnickname=\"x(测试号)\" content=\"\"  shortpy=\"XCSH\" imagestatus=\"3\" scene=\"6\" country=\"CN\" province=\"Hubei\" city=\"Wuhan\" sign=\"\" percard=\"1\" sex=\"1\" alias=\"xungong91\" weibo=\"\" weibonickname=\"\" albumflag=\"0\" albumstyle=\"0\" albumbgimgid=\"\" snsflag=\"49\" snsbgimgid=\"\" snsbgobjectid=\"0\" mhash=\"0178aa0380e771150b990e0c1654e6d5\" mfullhash=\"0178aa0380e771150b990e0c1654e6d5\" bigheadimgurl=\"http://wx.qlogo.cn/mmhead/ver_1/bk8A4VEZ9iatu8xSSKibcqoVmxsdD7XIia0s1Y4XJ3NJuLQqicEcg769hrdpicClEYlickBtL7BxKaWp1WQ6DmdWfgAg/0\" smallheadimgurl=\"http://wx.qlogo.cn/mmhead/ver_1/bk8A4VEZ9iatu8xSSKibcqoVmxsdD7XIia0s1Y4XJ3NJuLQqicEcg769hrdpicClEYlickBtL7BxKaWp1WQ6DmdWfgAg/132\" ticket=\"v2_bc7161d31f6676b6ff4032ce014faf8e39ecb05a650f4ac2b3b9b8defc90c85960af4981b37bf30819940fa4a96d96fe92b7a1b8654f27fe0c862b928bcb0d1c@stranger\" opcode=\"2\" googlecontact=\"\" qrticket=\"\" chatroomusername=\"\" sourceusername=\"\" sourcenickname=\"\"&gt;&lt;brandlist count=\"0\" ver=\"617220389\"&gt;&lt;/brandlist&gt;&lt;/msg&gt;"
	//
	//temp := WXConvertHtmlString(xmlData)
	//content := []byte(temp)
	//wxFmessageContent := WxFmessageContent{}
	//err := xml.Unmarshal(content, &wxFmessageContent)
	//if err != nil {
	//	panic("err:" + err.Error())
	//}

	temp := "0.01"
	num, _ := strconv.ParseFloat(temp, 64)
	fmt.Printf("%f\n", num)
	fmt.Printf("%0.2f\n", num)
}

type WxFmessageContent struct {
	XMLName      xml.Name `xml:"msg"` /* 根节点定义 */
	Fromusername string   `xml:"fromusername,attr"`
	Alias        string   `xml:"alias,attr"`
}

func WXConvertHtmlString(form string) (string) {
	form = strings.Replace(form, "&quot;", "\"", -1)
	form = strings.Replace(form, "&amp;", "&", -1)
	form = strings.Replace(form, "&lt;", "<", -1)
	form = strings.Replace(form, "&gt;", ">", -1)
	//strings.Replace(form, "&nbsp;", " ", -1)
	return form
}