/**
 * Created by lenovo on 2017/7/10.
 * lab2 by Zhou Xiao
 */
function Calculate() {
    this.firstEntry = document.getElementById("show");
    this.expression = '';
    /*
     * 检查运算符是否合法,第一个字符是除“-”以外的运算符都是非法的，最后一个字符是运算符，也是非法的；
     * 检查是否含有不合法的多运算符 “**”，“*\/”,"*+"，"*-","+*","++","+\/"以及两以上的连续运算符都是不允许的
     */
    this.checkOperator = function(expression) {
        var reg = /(^[\+\*\/])|([\+\-\*\/]$)|([\+\-\*\/][\+\*\/]+)|([\*\/](\-)+)|([\+\-](\-){2,})/;
        if(reg.test(expression)) {
            return false;
        }
        return true;
    };
    /*
     * 检查“.”是否在正确位置。
     */
    this.checkFloat = function (expression) {
        var reg = /(^\.)|(\.$)|([\+\-\*\/]\.)|(\.[\+\-\*\/])|((\d+\.+){2,}\d*)/;
        if (reg.test(expression)) {
            return false;
        }
        return true;
    };
    this.hasBracket = function(expression) {
        var hasBraketReg = /(|)/; //查看表达expression中是否有（）；
        if (hasBraketReg.test(expression)) {
            return true;
        }
        return false;
    };
    /*
     * 检查表达式中的输入的括号输入正确；
     * 括号必须与运算符号连接在一起 既“3（”，“（*3”，“3*）”，“）3”,".)",".(","(.",").",是不允许的
     * 左括号的数量必须等于右括号的数量
     */
    this.checkBracket = function(expression) {
        var reg = /([\d\.])|([\d\.])|([\+\-\*\/\.])|([\+\-\*\/\.])/;
        if (reg.test(expression)) {
            return false;
        }
        var leftBracket = 0, rightBracket = 0;
        for (var i = 0; i < expression.length; i++) {
            if (expression.charAt(i) === "(") {
                leftBracket++;
            } else if(expression.charAt(i) === ")") {
                rightBracket++;
            }
        }
        if (!(leftBracket === rightBracket)) {
            return false;
        }
        return true;
    };
    this.removeBracket = function(expression) {
        var regMatch = /[\(]+\)/g; //这个正则表达式匹配最里面的一层括号，既(这里面是不能包含“（”或是“）”的)
        var childExpression = expression.match(regMatch);
        var mySign = "&mySign&"; //用一个特殊标记记录等会需要替换的位置
        var replaceExpression = expression.replace(regMatch,mySign);
        var subExpression = "";
        for(var i = 0; i < childExpression.length; i++) {
            subExpression = childExpression[i].substring(1,childExpression[i].length-1);
            if (this.hasMultiplicOrDivision(subExpression)) {
                subExpression = this.removeMultiplicOrDivision(subExpression);
            }
            if (this.hasPlusOrMinus(subExpression)) {
                subExpression = this.plusOrMinus(subExpression);
            }
            replaceExpression = replaceExpression.replace(mySign,subExpression);
        }
        expression = replaceExpression;
        if(this.hasBracket(expression)) {
            expression = this.removeBracket(expression);
        } else {
            return expression;
        }
        return expression;
    };
    this.clean = function() {
        this.firstEntry.value = '0';
        this.expression = '';
    };
    this.deleteNumber = function() {
        this.expression = this.expression.substring(0,this.expression.length-1);
        this.firstEntry.value = this.expression;
    };
    this.showExpression = function(expression) {
        this.expression += expression;
        this.firstEntry.value = this.expression;
    };
    this.calculateResult = function() {
        var wrongMessage = "Invalid Input.";
        if (!this.checkOperator(this.expression) || !this.checkFloat(this.expression)) {
            this.firstEntry.value = wrongMessage;
            this.expression = '';
            return ;
        }
        if(this.hasBracket(this.expression)) {
            if (!this.checkBracket(this.expression)) {
                this.firstEntry.value = wrongMessage;
                this.expression = '';
                return ;
            }
            this.expression = this.removeBracket(this.expression);
        }
        if (this.hasMultiplicOrDivision(this.expression)) {
            this.expression = this.removeMultiplicOrDivision(this.expression);
        }
        if(this.hasPlusOrMinus(this.expression)) {
            this.expression = this.plusOrMinus(this.expression);
        }
        this.firstEntry.value = this.expression;
        this.expression = '';
    };
    this.hasMultiplicOrDivision = function(expression) {
        var hasMultiplicOrDivisionReg =  /(\*|\/)/;
        if (hasMultiplicOrDivisionReg.test(expression)) {
            return true;
        };
        return false;
    };
    this.removeMultiplicOrDivision = function(expression) {
        var regMatch = /((\d+\.?\d*)(\*|\/))+(\d+\.?\d*)/g;
        var childResult = "";
        var childExpression = expression.match(regMatch);
        var mySign = "&&"; //用一个特殊标记记录等会需要替换的位置
        var replaceExpression = expression.replace(regMatch,mySign);
        for(var i = 0; i < childExpression.length; i++) {
            childResult = this.multiplicOrDivision(childExpression[i]);
            replaceExpression = replaceExpression.replace(mySign,childResult);
        }
        expression = replaceExpression;
        return expression;
    };
    this.multiplicOrDivision = function(expression) {
        var regNumber = /\d+\.?\d*/g;
        var regOperator = /(\*|\/)/g;
        var arrNumbers = expression.match(regNumber);
        var arrOperators = expression.match(regOperator);

        var calResult = parseFloat(arrNumbers[0]);
        for (var i = 0; i < arrOperators.length; i++) {
            if (arrOperators[i] === '*') {
                calResult *= parseFloat(arrNumbers[i+1]);
            } else {
                calResult /= parseFloat(arrNumbers[i+1]);
            }
        }
        return calResult;
    };

    this.hasPlusOrMinus = function(expression) {
        var hasPlusOrMinusReg =  /(\+|\-)/;
        if (hasPlusOrMinusReg.test(expression)) {
            return true;
        };
        return false;
    };
    this.plusOrMinus = function(expression) {
        /*
         *  如果第一个字符是“-”号,就在expression前面加上一个0即可。
         */
        if (expression.charAt(0) === "-") {
            expression = 0 + expression;
        }
        var doubleMinusReg = /\-\-/;  //减去一个负数，等于加一个正数
        if (doubleMinusReg.test(expression)) {
            expression = expression.replace(doubleMinusReg,"+");
        }
        doubleMinusReg = /\+\-/;  //加上一负数，等于减去一个正数
        if (doubleMinusReg.test(expression)) {
            expression = expression.replace(doubleMinusReg,"-");
        }
        var regNumber = /\d+\.?\d*/g;
        var regOperator = /(\+|\-)/g;
        var arrNumbers = expression.match(regNumber);
        var arrOperators = expression.match(regOperator);

        var calResult = parseFloat(arrNumbers[0]);
        for (var i = 0; i < arrOperators.length; i++) {
            if (arrOperators[i] === '+') {
                calResult += parseFloat(arrNumbers[i+1]);
            } else {
                calResult -= parseFloat(arrNumbers[i+1]);
            }
        }
        return calResult;
    };
}

function pageLoad() {
    var calculate = new Calculate();
    var ACkeyButton = document.getElementsByClassName("ACkeyButton");
    ACkeyButton[0].onclick = function() {
        calculate.clean();
    };
    var deleteNumber = document.getElementById("deleteNumber");
    deleteNumber.onclick = function() {
        calculate.deleteNumber();
    };
    var calculateResult = document.getElementById("calculateResult");
    calculateResult.onclick = function () {
        calculate.calculateResult();
    };
    var keyButton = document.getElementsByClassName("keyButton");
    for (var i in keyButton) {
        keyButton[i].onclick = (function(index) {
            return function() {
                calculate.showExpression(keyButton[index].innerHTML);
            };
        })(i);
    }
}
