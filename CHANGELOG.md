

# Next release
[#155]: https://github.com/DoUML/douml/pull/155
[#161]: https://github.com/DoUML/douml/pull/161
[#167]: https://github.com/DoUML/douml/pull/167
[#170]: https://github.com/DoUML/douml/pull/170

* Fixed compilation on OS X El Capitan [#155]
* Fixed warning about duplicated uml entities showing up needlessly [#161]
* Build date and time automated [#161]
* Fixed mutually exclusive attribute menus when they should not be [#161] [#167]
* Fixed some keywords not being parsed by cpp reverse and roundtrip [#161]
* Some UI improvements [#161]
* Version bump [#161]
* Improvements regarding Qt5 style handling [#167]
* Crash fix and code improvements [#167]
* Missing specifiers of c++ operation added to CppReverse and CppRoundtrip [#167]
* Fix missing = sign in default and delete specifiers [#167]
* Reduce amount of warnings [#170]
* Warnings about deprecated use of Qt will be shown when compiling. [#170]
* Various improvements on Makefiles and .pro files [#170]
* The Makefile 'install' target on OS X now builds a .app bundle with all the executables inside (so that they can be launched from DoUML). For this reason only douml is still build as a bundle. Then macdeployqt adds needed frameworks and makes a .dmg file, but it's still very rough and needs more work (for instance, including all support files, translation, documentation, etc.) [#170]
* Added to the Makefile the target 'xcodeprojects' to generate Xcode projects. [#170]
* Changed some remaining "BoUML" text to "DoUML" [#170]
* Set a better size for the Image dialog box and its Browse button. [#170]
* Removed a misplaced text only appearing on Mac OS X in the Shortcut dialog. [#170]
* Fixed segmentation fault when quitting DoUML with opened project. [#170]

# v1.0.8
* Numerous bugfixes

# v1.0b7.4
* Fixed the crash at editing unidirectional association.

# v1.0b7.1 
* Fixed the crash that could occur if the user closed quick edit while editing param type
* Attribute and operations added through quick edit now appear at their proper places in main tree view
* Fixed operation propagation that got broken during previous releases

# v1.0b7.1 
* Fixed the issue that stopped app from closing rpoperly

# v1.0b7

* Previously, after "close window" button was clicked and user selected "Cancel" the app closed nevertheless. No longer the case.
* Fixed crash when reopening operation window that had different amount of KV-pairs
* Duplicated items in tree appear next to their source (valid of class, attribute, operation, extra member)
* Settings will now be craeted automatically if there is no file present.
* Fixed "relative path" for cpp generation.
* Added capability of adding enum items and class attributes to Quickedit window
* Added buttons for clipboard access and Quickedit to the toolbar
* List of recent projects now lives in settings.ini
* Updated "About" dialog and a new icon 

# v1.0b6
* Import/Export XMI2.1 are working now. Pls test for any possible bugs before fully embracing them.

# v1.0b5
* Duplicating class, operation and attribute produces its name in the name request edit.
* Vastly expanded functionality of Quickedit window. 
* Repeatedly pressing "ctrl-e" closes it if it is already open
* It will remember the state it was in prior to close and restore itself accordingly.
* Almost all features necessary for C++ editing are present. 
* Postfix/prefix columns in quickedit table mean how parameter is actually passed in the function where: const/volatile(prefix), \*,&(postfix) 
* You can add operation by clicking on +Operation button if you are currently on the operation or class node.
* You can add operation parameters by clicking on +Parameter button if you are on an attribute or operation node.
* You can delete all nodes by clicking on "Delete" column. Deleting is done in Bouml way where "deleted" node is marked as deleted but is not actually deleted until program is closed.
A thing to note - operation parameters are also deleted in this way, but they are only present in their "deleted" state until window is closed or trr is filtered.
10. You can move operation parameters within a single function (I will expand this later). To move parameters - click on their "mark" column, then right click on parameter you want to move them to and select either "Move after" or "Move before"
11. If you do not ant to see c++ columns in the table - untick "C++" checkbox on the top of the window.
!. There is a drawback to using this window atm - it knows nothing of propagation through hierarchy. Once You've edited an operation - make sure to make same edits in the others.
!!. Quickedit, at the moment, knows _nothing_ of the changes you make in the other dialogs, if you are using it in windowed mode - make sure to press refresh button on the top left after you've changed stuff! Although I'd recommend closing it immediately after you edited what you wanted and reopening with correct data later.

Now the only major things missing from Quickedit are management of enums and adding attributes to classes. These will be added in the next version.


# v1.0b4
Added a new class/operation/parameter control. It is brought up by pressing Ctlr-E on Package, Classview, Class, Operation or Attribute nodes in main tree
This control is essentially an alternative way to insert quick fixes into class hierarchy. 
Things of note:
* you can quickly search for classes/operation etc... by entering text in lineedit on the top. It even picks operation parameters!
* two buttons to the left of the search lineedit allow you to expand/collapse whole levels in the tree
* "Type" of an operation node is actually its return type.
* Nodes below operations are their parameters
* Changes made into editable cells are IMMEDIATELY done to the model. So far there is no rollback once you've edited something.
* Classviews/Packages are not shown in the tree, but they are used to create it.

Currently, the changes you can insert in this editor are limited, and some buttons are disabled but you can expect to have MUCH more control from it in later versions.
Feedback and requests will be appreciated.



# v1.0b3
* App entered endless cycle while trying to open some diagrams. Fixed


# v1.0b2

## Changes
* Previously, opened tab was saved in operation dialog between dialog opens.This turned out to be very anoying and is now disabled.


## Bugfixes
* cpp header file was not produced correctly on generation of new projects.
* Deploy plugin was freezing on some classes due to some weird bug which involved ->bytesAvailable function to return different value than what was written to socket.
* Mini toolbar could crash when user tried navigating above the highest node via arrow buttons.
* Some icons were not shown in minit-toolbar.
* "Unmark all" did not change the color of generator label.
* Propagating changes from abstract operation will not null op definition in subclasses.
* Clicking OK in relations dialog while ot editing relation's name produced "illegal name" error.
* static class members were incorrectly given "= {$value] " when generated in cpp headers.
* In Properties tables around the app pressing enter or any arrow button finished editing of the cell.
* Reopening class dialog did not properly reinitialize formals/inheritance/properties.
* Reopening operation dialog did not properly reinitialize exceptions.


## Features
* Added "Catalog" widget below class tree. This widget is used for quick tree navigation and has 3 tabs.
* "Visited" tab updates each time user clicks on a node in a tree. This node is inserted into visited and clicking on it will.
  immediately scroll the main tree to it.
* "Marked" tab tracks user selection and serves double purpose of tree navigation(as in "Visited") and node deselection via rightclick menu.
* "Favourites" tab is used when user ahs often visited tree nodes and wants an easy wasy to return to the in a tree.
* Adding nodes s done by dragging them from the main tree onto favourites tabs.
* Catalog widget has line edit under tabs which serves the purpose of filtering the Visited view (only Visited atm).
* "Builtin types" tab in generation settings has been completely reworked. 
* User can now search and sort it.
* User can selectively turn off languages he does not use in the table.
* When a new row is being produced it is initialized with enough defaults to make assigning UML name the only obligatory edit before clicking "OK".
* Adding new rows is now done through "Add type" button and a few options were removed from "do" menu as they no longer make sense.
