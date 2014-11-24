Judger\Proposition 判官\命题人
==============================

This directory includes the proposition programs which will gather proposition answers from Kyuyu mongo databases.

本目录下包含判官程序的所有命题程序，这些程序会从 Kyuyu 的 mongoDB 数据库中分析命题的答案。

Questions  题目
---------------

1. 你的名字是三个字的吗？

    >> { name: /^.{3}$/ }

2. 行政大区

    1. 你的家乡在华北吗？

        >> { hometown: { $in: ["北京", "天津", "河北", "山西", "内蒙古"] } }

        count: 19

    2. 你的家乡在西北吗？

        >> { hometown: { $in: ["陕西", "青海", "甘肃", "新疆", "宁夏"] } }
        count: 22

    3. 你的家乡在东北吗？

        >> { hometown: { $in: ["黑龙江", "辽宁", "吉林"] } }

        count: 14

    4. 你的家乡在华东吗？

        >> { hometown: { $in: ["江苏", "浙江", "安徽", "福建", "江西", "山东", "上海"] } }

        count: 54

    5. 你的家乡在华中吗？

        >> { hometown: { $in: ["河南", "湖北", "湖南"] } }

        count: 18

    6. 你的家乡在华南吗？

        >> { hometown: { $in: ["广东", "海南", "广西", "香港", "澳门"] } }
        count: 17

    7. 你的家乡在西南吗？

        >> { hometown: { $in: ["重庆", "四川", "贵州", "云南", "西藏"] } }
        count: 24

3. 你的家乡在直辖市吗？

    >> { hometown: { $in: ["重庆", "上海", "北京", "天津"] } }

    count: 23

4. 你住在西南一楼吗？

    >> { gender: "M" }

5. 你出生于 1996 年吗？

    >> { $where: "/^.{6}1996/i.test(this.citizen_id+'')" }

    count: 94

6. 星座 

    1. 你的星座是 白羊座 吗？

        >> { $where: "parseFloat((this.citizen_id+'').substr(10, 4)) >= 321 && parseFloat((this.citizen_id+'').substr(10, 4)) <= 420 " }

        count: 16

    2. 你的星座是 金牛座 吗？

        >> { $where: "parseFloat((this.citizen_id+'').substr(10, 4)) >= 421 && parseFloat((this.citizen_id+'').substr(10, 4)) <= 520 " }
        
        count: 12

    3. 你的星座是 双子座 吗？

        >> { $where: "parseFloat((this.citizen_id+'').substr(10, 4)) >= 521 && parseFloat((this.citizen_id+'').substr(10, 4)) <= 621 " }

        count: 10

    4. 你的星座是 巨蟹座 吗？

        >> { $where: "parseFloat((this.citizen_id+'').substr(10, 4)) >= 622 && parseFloat((this.citizen_id+'').substr(10, 4)) <= 722 " }

        count: 18

    5. 你的星座是 狮子座 吗？

        >> { $where: "parsefloat((this.citizen_id+'').substr(10, 4)) >= 723 && parsefloat((this.citizen_id+'').substr(10, 4)) <= 822 " }

        count: 12

    6. 你的星座是 处女座 吗？

        >> { $where: "parseFloat((this.citizen_id+'').substr(10, 4)) >= 823 && parseFloat((this.citizen_id+'').substr(10, 4)) <= 922 " }

        count: 17

    7. 你的星座是 天秤座 吗？

        >> { $where: "parseFloat((this.citizen_id+'').substr(10, 4)) >= 923 && parseFloat((this.citizen_id+'').substr(10, 4)) <= 1022 " }

        count: 14

    8. 你的星座是 天蝎座 吗？

        >> { $where: "parseFloat((this.citizen_id+'').substr(10, 4)) >= 1023 && parseFloat((this.citizen_id+'').substr(10, 4)) <= 1121 " }

        count: 19

    9. 你的星座是 射手座 吗？

        >> { $where: "parseFloat((this.citizen_id+'').substr(10, 4)) >= 1122 && parseFloat((this.citizen_id+'').substr(10, 4)) <= 1221 " }

        count: 13

    10. 你的星座是 摩羯座 吗？

        >> { $where: "parseFloat((this.citizen_id+'').substr(10, 4)) >= 1222 || parseFloat((this.citizen_id+'').substr(10, 4)) <= 119 " }

        count: 14

    11. 你的星座是 水瓶座 吗？

        >> { $where: "parseFloat((this.citizen_id+'').substr(10, 4)) >= 120 && parseFloat((this.citizen_id+'').substr(10, 4)) <= 218 " }

        count: 12

    12. 你的星座是 双鱼座 吗？

        >> { $where: "parseFloat((this.citizen_id+'').substr(10, 4)) >= 219 && parseFloat((this.citizen_id+'').substr(10, 4)) <= 320 " }

        count: 9

7. 手机尾号

    1. 你的手机尾号是 1 吗？

        >> { $where : "this.mobile%10 == 1" }

    2. 你的手机尾号是 2 吗？

        >> { $where : "this.mobile%10 == 2" }

    3. 你的手机尾号是 3 吗？

        >> { $where : "this.mobile%10 == 3" }

    4. 你的手机尾号是 4 吗？

        >> { $where : "this.mobile%10 == 4" }

    5. 你的手机尾号是 5 吗？

        >> { $where : "this.mobile%10 == 5" }

    6. 你的手机尾号是 6 吗？

        >> { $where : "this.mobile%10 == 6" }

    7. 你的手机尾号是 7 吗？

        >> { $where : "this.mobile%10 == 7" }

    8. 你的手机尾号是 8 吗？

        >> { $where : "this.mobile%10 == 8" }

    9. 你的手机尾号是 9 吗？

        >> { $where : "this.mobile%10 == 9" }

    10. 你的手机尾号是 0 吗？

        >> { $where : "this.mobile%10 == 0" }

8. 你在班级中有职位吗？

    >> { post: {$ne: ""} }

9. 你是女生吗？

    >> { gender: "F" };

10. 学号尾号

    1. 你的学号尾号是 1 吗？
    
        >> { $where : "this._id%10 == 1" }

    2. 你的学号尾号是 2 吗？

        >> { $where : "this._id%10 == 2" }

    3. 你的学号尾号是 3 吗？

        >> { $where : "this._id%10 == 3" }

    4. 你的学号尾号是 4 吗？

        >> { $where : "this._id%10 == 4" }

    5. 你的学号尾号是 5 吗？

        >> { $where : "this._id%10 == 5" }

    6. 你的学号尾号是 6 吗？

        >> { $where : "this._id%10 == 6" }

    7. 你的学号尾号是 7 吗？

        >> { $where : "this._id%10 == 7" }

    8. 你的学号尾号是 8 吗？

        >> { $where : "this._id%10 == 8" }

    9. 你的学号尾号是 9 吗？

        >> { $where : "this._id%10 == 9" }

    10. 你的学号尾号是 0 吗？

        >> { $where : "this._id%10 == 0" }

11. 你住在宿舍二楼吗？
    
    >> { $where: "/^1/i.test(this.room+'')" }
