/**
 * HW1
 * Author: Bao Tran Tran Do
 *
 * Version 1.2
 * 1/22/2022
 */

import 'dart:convert';
import 'dart:io';
import 'package:flutter/material.dart';
import 'package:hw1/model/todo_model.dart';
import 'package:path_provider/path_provider.dart';
import 'package:provider/provider.dart';
import '../storage/storage.dart';
import 'package:qr_flutter/qr_flutter.dart';
import 'package:syncfusion_flutter_pdf/pdf.dart';
import 'package:open_file/open_file.dart';
/***
 * A separate to display that specific todos attributes. Similar to the UI
 * of the individual task card content. Only display the status of the
 * relation type and the relation task card if the user enter it correctly.
 * As of now it will only be 1 to many relationship not many to many relationship
 */

class DisplayTodoSharedPage extends StatefulWidget{
  final TodoModel todo;
  DisplayTodoSharedPage({
    required this.todo,
  });



  // https://api.flutter.dev/flutter/widgets/StatefulWidget-class.html
  @override
  _DisplayTodoContentState createState() => _DisplayTodoContentState(todo: todo);
}

/**
 * Private class for the homepage
 */
class _DisplayTodoContentState extends State<DisplayTodoSharedPage> {
  final TodoModel todo;

  _DisplayTodoContentState({
    required this.todo,
  });


  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('HW: Bao Tran Do\'s Do -> Display The Todo'),
      ),
      body: buildTodo(context),

    );

  }
  @override
  Widget buildTodo(BuildContext context) =>
      Container(
        key: Key('TodoContent'),
        color: Color(0xFFFBE9E7),
        padding: EdgeInsets.all(15),
        child: Row(
          children: [
            const SizedBox(width: 20),
            Expanded(
              child: Column(
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [

                  // The title of the todos display
                  Text(
                    'Title: ' + todo.title,
                    style: TextStyle(
                      fontWeight: FontWeight.bold,
                      color: Theme.of(context).primaryColor,
                      fontSize: 30,
                    ),
                  ),

                  Container(
                    margin: EdgeInsets.only(top: 5),
                    child: Text(
                      'Status:   '+ todo.status,
                      style: TextStyle(
                        fontWeight: FontWeight.bold,
                        color: Colors.purple,
                        fontSize: 25,
                      ),
                    ),
                  ),

                  Container(
                    margin: EdgeInsets.only(top: 5),
                    child: Text(
                      'ID:   '+ todo.id.toString(),
                      style: TextStyle(
                        color: Colors.black87,
                        fontSize: 15,
                      ),
                    ),
                  ),

                  Container(
                    margin: EdgeInsets.only(top: 5),
                    child: Text(
                      'Created Time:   '+ todo.createdTime.toString(),
                      style: TextStyle(
                        color: Colors.black87,
                        fontSize: 15,
                      ),
                    ),
                  ),

                  if(todo.relationType != 'None' && titleName(context) != '' && todo.id != todo.relatedTo && todo.relationType != '')
                    Container(
                      margin: EdgeInsets.only(top: 5),
                      child: Text(
                        'RelationType:   '+ todo.relationType.toString(),
                        style: TextStyle(
                          color: Colors.black87,
                          fontSize: 15,
                        ),
                      ),
                    ),


                  if(titleName(context) != '' && todo.relationType != 'None' && todo.relationType != ''  && todo.id != todo.relatedTo)
                    Container(
                      margin: EdgeInsets.only(top: 5),
                      child: Text(
                        'Task card ID: '+ todo.relatedTo + '    Task card name: '+ titleName(context),
                        style: TextStyle(
                          color: Colors.black87,
                          fontSize: 15,
                        ),
                      ),
                    ),


                  if(titleName(context) != '' && todo.relationType != 'None' && todo.relationType != ''  && todo.id != todo.relatedTo)
                    TextButton(
                      style: TextButton.styleFrom(
                        textStyle: const TextStyle(fontSize: 15),
                      ),
                      onPressed: () {displayTodoContent(context,todo);},
                      child: const Text('Go to related task...'),
                    ),

                  if(titleName(context) != '' && todo.relationType != 'None' && todo.relationType != ''  && todo.id != todo.relatedTo)
                    TextButton(
                      style: TextButton.styleFrom(
                        textStyle: const TextStyle(fontSize: 15,),
                      ),
                      onPressed: () {removeRelationContent(context,todo);},
                      child: const Text('Remove the related task...', ),
                    ),
                  Row(
                    children: [
                      Container(
                        height: 120,
                        width: 120,
                        color: Colors.black38,
                        child: todo.imageFile == '' ? Icon(Icons.image,)
                            : Image.memory(base64Decode(todo.imageFile)),

                      ),

                      QrImage(
                        data: todo.title,
                        version: QrVersions.auto,
                        size: 140,
                        gapless: false,
                      )

                    ],
                  ),

                  //If we have the description we want to display the description
                  if(todo.description.isNotEmpty)
                    Container(
                      margin: EdgeInsets.only(top: 15),
                      child: Text(
                        'Description: ' + todo.description,
                        style: TextStyle(
                          fontSize: 22,
                        ),
                      ),
                    ),

                ],
              ),
            ),
          ],
        ),


      );


  /***
   * Function to retrieve the related todods id's title
   */
  String titleName(BuildContext context){
    final provider = Provider.of<TodosStorage>(context,listen: false);
    var titleId = todo.relatedTo;
    for(var i in provider.firebaseTodos){
      if(titleId == i.id.toString()){
        return i.title.toString();
      }
    }

    return "";
  }

  /***
   * Retrieve all the TodoModel of the related todos.
   */
  TodoModel relatedTodo(BuildContext context){
    final provider = Provider.of<TodosStorage>(context,listen: false);
    var titleId = todo.relatedTo;

    for(var i in provider.firebaseTodos) {
      if (titleId.toString() == i.id.toString()) {
        return i;
      }
    }
    return todo;
  }

  /**(
   * Routing to the page that display all of the task attributes
   */
  void displayTodoContent(BuildContext context, TodoModel todo) => Navigator.of(context).push(
    MaterialPageRoute(builder: (context) => DisplayTodoSharedPage(todo:relatedTodo(context))),
  );

  /***
   * This function will remove the user's relation and the task card of it
   */
  void removeRelationContent(BuildContext context, TodoModel todo) {
    final provider = Provider.of<TodosStorage>(context,listen: false);
    provider.removeRelationSharedTodo(todo);
    Navigator.of(context).pop();
  }

}






