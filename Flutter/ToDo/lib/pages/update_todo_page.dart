/**
 * HW1
 * Author: Bao Tran Tran Do
 * Version 1.2
 * 1/22/2022
 */

import 'dart:convert';

import 'package:flutter/material.dart';
import 'package:image_picker/image_picker.dart';
import 'package:provider/provider.dart';
import 'package:hw1/model/todo_model.dart';
import 'package:hw1/storage/storage.dart';
import 'package:hw1/widget/todo_form_inputs_widget.dart';
import 'dart:io';
/***
 * This class will take the user to a separate page to modify the title and
 * the description and the related task card id and also the relationship type
 */
class UpdateTodoPage extends StatefulWidget{

  // Declared the variables
  final TodoModel todo;


  // Constructor
  UpdateTodoPage({
    required this.todo,
  });

  @override
  _UpdateTodoPageState createState() => _UpdateTodoPageState();
}

/***
 * Private class for the state of edit todos page.
 */
class _UpdateTodoPageState extends State<UpdateTodoPage> {
  final _formKey = GlobalKey<FormState>();
  String title='';
  String description ='';
  String status = '';
  String relationType = "None";
  String dropdownRelationValue = 'None';
  String relatedTo = '';
  String currentTaskCardID = '';
  String imageFile = '';
  ImagePicker image = ImagePicker();
  bool firebase = false;

  @override
  /***
   *   Need to call for the current data to be displayed on the card
   */
  void initState() {
    title = widget.todo.title;
    description = widget.todo.description;
    relationType = widget.todo.relationType;
    relatedTo = widget.todo.relatedTo;
    currentTaskCardID = widget.todo.id.toString();
    imageFile = widget.todo.imageFile;
    firebase = widget.todo.firebase;
    super.initState();
  }

  @override
  /**
   * Layout of the edit page
   */
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('HW: Bao Tran Do\'s Do -> Edit The Todo'),
      ),

      body: ListView(
        children: [
          Container(

            // The todos form layout with the current information
            child: Column(
              children: [
                Center(
                  child: Row(
                    children: [

                      // display the image
                      Center(
                        child: Row(
                          children: [
                            Container(
                              height: 80,
                              width: 80,
                              color: Colors.black38,
                              child: imageFile == '' ? Icon(Icons.image,)
                                  : Image.memory(base64Decode(imageFile)),
                            ),

                            // buttons to select whether they want camera or gallery
                            Column(
                              children: [
                                MaterialButton(
                                  onPressed: () {
                                    getGallery();
                                  },
                                  height: 20,
                                  color: Colors.teal,
                                  child: Text(
                                    "gallery",
                                    style: TextStyle(
                                      color: Colors.white,
                                    ),
                                  ),
                                ),
                                MaterialButton(
                                  onPressed: () {
                                    getCamera();
                                  },
                                  height: 20,
                                  color: Colors.teal,
                                  child: Text(
                                    "camera",
                                    style: TextStyle(
                                      color: Colors.white,
                                    ),
                                  ),
                                ),
                              ],
                            ),
                          ],
                        ),
                      ),
                    ],
                  ),

                ),


                Text(
                    '(Current relation: ' + relationType + ')',
                    // text style
                    style: TextStyle(
                      fontWeight: FontWeight.bold,
                      fontSize: 10,
                      color: Colors.blueGrey,
                    )
                ),

                Text(
                    'Select new relation type...',
                    // text style
                    style: TextStyle(
                      fontWeight: FontWeight.bold,
                      fontSize: 10,
                      color: Colors.blueGrey,
                    )
                ),

                Container(
                  height: 55.0,
                  child: DropdownButtonFormField(
                    decoration: InputDecoration(
                      enabledBorder: OutlineInputBorder(
                        borderSide: BorderSide(color: Colors.black),
                      ),
                      filled: true,
                      fillColor: Colors.blueGrey[100],
                    ),

                    dropdownColor: Colors.blueGrey[100],
                    value: dropdownRelationValue,
                    onChanged: (String? newValue) {
                      setState(() {
                        dropdownRelationValue = newValue!;
                      });
                    },

                    items: <String>['None', 'is subtask of', 'is blocked by', 'is alternative to', 'is duplicate to', 'is least priority to', 'is top priority to'].map<DropdownMenuItem<String>>((String value) {
                      return DropdownMenuItem<String>(
                        value: value,
                        child: Text(value,),
                      );
                    }).toList(),

                  ),
                ),

                // Adding spaces
                Container(height: 5),

                if(titleName(context) == '')
                  Text(
                      'The related task card ID you enter does not exist...enter a valid ID',
                      // text style
                      style: TextStyle(
                        fontWeight: FontWeight.bold,
                        fontSize: 10,
                        color: Colors.red,
                      )
                  ),

                if(currentTaskCardID == relatedTo)
                  Text(
                      'Cannot use the current card ID to set relations!',
                      // text style
                      style: TextStyle(
                        fontWeight: FontWeight.bold,
                        fontSize: 10,
                        color: Colors.red,
                      )
                  ),

                // Adding spaces
                Container(height: 5),



                // Adding spaces
                Container(height: 5),

                if(firebase == false)
                  Form(
                    child: TodoFormInputsWidget(
                      title: title,
                      description: description,
                      relatedTo: relatedTo,
                      userTitle: (title) => setState(() => this.title = title),
                      userDescription: (description) => setState(() => this.description = description),
                      userRelatedTo: (relatedTo) => setState(() => this.relatedTo = relatedTo),
                      savedTodo: updatePersonalTodo,
                    ),
                    key: _formKey,
                  ),

                if(firebase == true)
                  Form(
                    child: TodoFormInputsWidget(
                      title: title,
                      description: description,
                      relatedTo: relatedTo,
                      userTitle: (title) => setState(() => this.title = title),
                      userDescription: (description) => setState(() => this.description = description),
                      userRelatedTo: (relatedTo) => setState(() => this.relatedTo = relatedTo),
                      savedTodo: updateSharedTodo,
                    ),
                    key: _formKey,
                  ),

              ],

            ),
            padding: EdgeInsets.all(25),
          ),
        ],
      ),
    );
  }

  /***
   * This function will update the user's todos to the storage
   */
  void updateSharedTodo() {
    final provider = Provider.of<TodosStorage>(context,listen: false);
    provider.updateFirebaseTodo(widget.todo,title,description,relationType=dropdownRelationValue, relatedTo,imageFile);
    // Once the user hit save. Get out of the screen
    Navigator.of(context).pop();
  }


  /***
   * This function will update the user's todos to the storage
   */
  void updatePersonalTodo() {
    final provider = Provider.of<TodosStorage>(context,listen: false);
    provider.updateTodo(widget.todo,title,description,relationType=dropdownRelationValue, relatedTo,imageFile);
    // Once the user hit save. Get out of the screen
    Navigator.of(context).pop();
  }

  /***
   * Function to retrieve the related todods id's title
   */
  String titleName(BuildContext context){
    final provider = Provider.of<TodosStorage>(context,listen: false);
    var titleId = relatedTo;

    if(firebase == false)
      for(var i in provider.todos){
        if(titleId == i.id){
          return i.title.toString();
        }
      }

    if(firebase == true)
      for(var i in provider.firebaseTodos){
        if(titleId == i.id){
          return i.title.toString();
        }
      }
    return "";
  }

  /**
   * This function is to get the camera and encode the image to save it to the database
   */
  getCamera() async {
    var img = await image.pickImage(source: ImageSource.camera);
    if(img != null) {
      setState(() {
        File filename = File(img!.path);
        List<int> name =filename.readAsBytesSync();
        imageFile = base64Encode(name);
      });
    }
  }

  /**
   * This function is to get the gallery and encode the image to save it to the database
   */
  getGallery() async {
    var img = await image.pickImage(source: ImageSource.gallery);
    if(img != null){
      setState(() {
        File filename = File(img!.path);
        List<int> name =filename.readAsBytesSync();
        imageFile = base64Encode(name);
      });
    }
  }
}