function SDMenu(id) {
	if (!document.getElementById || !document.getElementsByTagName)
		return false;
	this.menu = document.getElementById(id);
	this.submenus = this.menu.getElementsByTagName("div");
	this.remember = true;
	this.speed = 3;
	this.markCurrent = true;
	this.oneSmOnly = false;
}
SDMenu.prototype.init = function() {
	var mainInstance = this;
	// for (var i = 0; i < this.submenus.length; i++)
	//	this.submenus[i].getElementsByTagName("span")[0].onclick = function() {
	//		mainInstance.toggleMenu(this.parentNode);
	//	};
	if (this.markCurrent) {
		var links = this.menu.getElementsByTagName("a");
		var link = null;
		for (var i = 0; i < links.length; i++) {
			if (document.location.href.indexOf(links[i].href) >= 0) {
				if (!link || (links[i].href.length > link.href.length)) {
					link = links[i];
				}
			}
	        }
		if (link) {
                        link.className = "current";
                        link.parentNode.className = "";
		}
	}
	if (this.remember) {
		var regex = new RegExp("sdmenu_" + encodeURIComponent(this.menu.id) + "=([01]+)");
		var match = regex.exec(document.cookie);
		if (match) {
			var states = match[1].split("");
			for (var i = 0; i < states.length; i++)
				this.submenus[i].className = (states[i] == 0 ? "collapsed" : "");
		}
	}
};
SDMenu.prototype.toggleMenu = function(submenu) {
	if (submenu.className == "collapsed")
		this.expandMenu(submenu);
	else
		this.collapseMenu(submenu);
};
SDMenu.prototype.myToggleMenu = function(submenu, url) {
        if (submenu.className == "collapsed")
		document.location = url;
        else
                this.collapseMenu(submenu);
};
SDMenu.prototype.expandMenu = function(submenu) {
	var fullHeight = submenu.getElementsByTagName("span")[0].offsetHeight;
	var links = submenu.getElementsByTagName("a");
	for (var i = 0; i < links.length; i++)
		fullHeight += links[i].offsetHeight;
	var moveBy = Math.round(this.speed * links.length);
	
	var mainInstance = this;
	var intId = setInterval(function() {
		var curHeight = submenu.offsetHeight;
		var newHeight = curHeight + moveBy;
		if (newHeight < fullHeight)
			submenu.style.height = newHeight + "px";
		else {
			clearInterval(intId);
			submenu.style.height = "";
			submenu.className = "";
			mainInstance.memorize();
		}
	}, 30);
	this.collapseOthers(submenu);
};
SDMenu.prototype.collapseMenu = function(submenu) {
	var minHeight = submenu.getElementsByTagName("span")[0].offsetHeight;
	var moveBy = Math.round(this.speed * submenu.getElementsByTagName("a").length);
	var mainInstance = this;
	var intId = setInterval(function() {
		var curHeight = submenu.offsetHeight;
		var newHeight = curHeight - moveBy;
		if (newHeight > minHeight)
			submenu.style.height = newHeight + "px";
		else {
			clearInterval(intId);
			submenu.style.height = "";
			submenu.className = "collapsed";
			mainInstance.memorize();
		}
	}, 30);
};
SDMenu.prototype.collapseOthers = function(submenu) {
	if (this.oneSmOnly) {
		for (var i = 0; i < this.submenus.length; i++)
			if (this.submenus[i] != submenu && this.submenus[i].className != "collapsed")
				this.collapseMenu(this.submenus[i]);
	}
};
SDMenu.prototype.expandAll = function() {
	var oldOneSmOnly = this.oneSmOnly;
	this.oneSmOnly = false;
	for (var i = 0; i < this.submenus.length; i++)
		if (this.submenus[i].className == "collapsed")
			this.expandMenu(this.submenus[i]);
	this.oneSmOnly = oldOneSmOnly;
};
SDMenu.prototype.collapseAll = function() {
	for (var i = 0; i < this.submenus.length; i++)
		if (this.submenus[i].className != "collapsed")
			this.collapseMenu(this.submenus[i]);
};
SDMenu.prototype.memorize = function() {
	if (this.remember) {
		var states = new Array();
		for (var i = 0; i < this.submenus.length; i++)
			states.push(this.submenus[i].className == "collapsed" ? 0 : 1);
		var d = new Date();
		d.setTime(d.getTime() + (30 * 24 * 60 * 60 * 1000));
		document.cookie = "sdmenu_" + encodeURIComponent(this.menu.id) + "=" + states.join("") + "; expires=" + d.toGMTString() + "; path=/";
	}
};

// <![CDATA[
var myMenu;
window.onload = function() {
	myMenu = new SDMenu("my_menu");
	myMenu.speed = 5;
	myMenu.oneSmOnly = true;
	myMenu.remember = false; 
	myMenu.markCurrent = true;
	myMenu.init();
};
// ]]>

/* --------------------------
Serach box behavior
----------------------------- */
function MM_setTextOfTextfield(objId,x,newText) { //v9.0
  with (document){ 
  	if (getElementById){
    	var obj = getElementById(objId);
	}
	if (obj) {
		if (x == "onclick") {
			obj.style.color = "#000000";
			obj.style.opacity = "1";
			obj.style.filter = "alpha(opacity=100)";
			if (obj.value == "Search...") obj.value = "";
		}
		if (x == "onblur") {
			obj.style.color = "#999999";
			obj.style.opacity = ".5";
			obj.style.filter = "alpha(opacity=50)";
			if (obj.value == "") obj.value = "Search...";
		}
	}
  }
}
