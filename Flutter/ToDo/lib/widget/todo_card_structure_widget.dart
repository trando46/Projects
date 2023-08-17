/**
 * HW1
 * Author: Bao Tran Tran Do
 * 1/16/2022
 */

import 'dart:convert';
import 'dart:io';

import 'package:cloud_firestore/cloud_firestore.dart';
import 'package:flutter/material.dart';
import 'package:hw1/storage/storage.dart';
import 'package:hw1/widget/todo_form_inputs_widget.dart';
import 'package:image_picker/image_picker.dart';
import 'package:provider/provider.dart';
import 'package:hw1/model/todo_model.dart';


/***
 * Creating the dialog of the todos. Using the stateful widget since the state
 * can be changeable. All the task cards that are created will be mark as 'open'
 */
class TodoCardStructureWidget extends StatefulWidget {
  @override
  _TodoCardStructureWidgetState createState() => _TodoCardStructureWidgetState();
}

/**
 * private class for the state
 *
 * Source: https://docs.flutter.dev/cookbook/forms/validation
 * Source: https://api.flutter.dev/flutter/material/AlertDialog-class.html
 */
class _TodoCardStructureWidgetState extends State<TodoCardStructureWidget>{
  // Global key that is unique for identifying the form widget
  // and to have validation of the form
  final _formKey = GlobalKey<FormState>();
  // This is storing the task information card
  String title = '';
  String description = '';
  String status = '';
  String relationType = "None";
  String dropdownRelationValue = 'None';
  String relatedTo = '';
  String dropdownRelatedToValue = 'None';
  String relationTypeValue = '';
  final listID = [];
  String imageFile = '';
  ImagePicker image = ImagePicker();
  String dropdownSharedValue = 'Shared';


  @override
  Widget build(BuildContext context) => ListView(
    children: [AlertDialog (

  content: Form(
  key: _formKey,

    // Want to put the data inside the column
    child: Column(
      mainAxisSize: MainAxisSize.min,
      children: [

        // The text header for the task card
        Text(
            'Add Todo',
            // text style
            style: TextStyle(
              fontWeight: FontWeight.bold,
              fontSize: 20,
              color: Colors.blueGrey,
            )
        ),

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

          // buttons to select if they want camera or gallery
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



        // Adding spaces
        Container(height: 5),

        Text(
            'Share?... ',
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
            value: dropdownSharedValue,
            onChanged: (String? newValue) {
              setState(() {
                dropdownSharedValue = newValue!;
              });
            },

            items: <String>['Personal', 'Shared'].map<DropdownMenuItem<String>>((String value) {
              return DropdownMenuItem<String>(
                value: value,
                child: Text(value,),
              );
            }).toList(),
          ),
        ),

        // Adding spaces
        Container(height: 5),



        // Adding spaces
        Container(height: 5),

        Text(
            'Relation type... ',
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

        Text(
            'Related to... ',
            // text style
            style: TextStyle(
              fontWeight: FontWeight.bold,
              fontSize: 10,
              color: Colors.blueGrey,
            )
        ),

        // Adding spaces
        Container(height: 5),

        if(this.dropdownSharedValue == 'Personal')
        // The form for the task card to fill out and save the users input
          TodoFormInputsWidget(
            userTitle: (title) => setState(() => this.title = title),
            userDescription: (description) => setState(() => this.description = description),
            userRelatedTo: (relatedTo) => setState(() => this.relatedTo = relatedTo),
            savedTodo: addTodo,
          ),

        if(this.dropdownSharedValue == 'Shared')
          TodoFormInputsWidget(
            userTitle: (title) => setState(() => this.title = title),
            userDescription: (description) => setState(() => this.description = description),
            userRelatedTo: (relatedTo) => setState(() => this.relatedTo = relatedTo),
            savedTodo: sharedTodo,
          ),


      ],
    ),
  ),
    ),
     ],
  );

  Future sharedTodo() async{

    final todo = TodoModel(
      title: title,
      description: description,
      //id: DateTime.now().toString(),
      //id: "",
      relatedTo: relatedTo,
      createdTime: DateTime.now(),
      status: 'Open',
      relationType: dropdownRelationValue,
      imageFile: imageFile,
      firebase: true,
    );

    // Call the provider
    final provider = Provider.of<TodosStorage>(context,listen: false);
    provider.idCounter(todo);
    provider.addTodoFirebase(todo);



    // Once the user hit save. Get out of the screen
    Navigator.of(context).pop();

  }

  
  /***
   * This function will add the user's todos to the storage
   *
   * Source: https://pub.dev/packages/provider
   */
  void addTodo() {
    // Add the todos to the list
    final todo = TodoModel(
      title: title,
      description: description,
      //id: DateTime.now().toString(),
      //id: "",
      relatedTo: relatedTo,
      createdTime: DateTime.now(),
      status: 'Open',
      relationType: dropdownRelationValue,
      imageFile: imageFile,
    );

    // Call the provider
    final provider = Provider.of<TodosStorage>(context,listen: false);
    //provider.idCounter(todo);
    provider.addTodoSQLDatabase(todo);
    // Once the user hit save. Get out of the screen
    Navigator.of(context).pop();
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