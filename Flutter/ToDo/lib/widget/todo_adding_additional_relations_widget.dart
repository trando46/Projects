/**
 * HW2
 * Author: Bao Tran Tran Do
 * 1/22/2022
 */

import 'package:flutter/material.dart';
import 'package:hw1/storage/storage.dart';
import 'package:hw1/widget/todo_form_inputs_widget.dart';
import 'package:provider/provider.dart';
import 'package:hw1/model/todo_model.dart';
import 'package:hw1/widget/todo_related_to_form_widget.dart';


class TodoAddingAdditionalRelationsWidget extends StatefulWidget {
  @override
  _TodoAddingAdditionalRelationsState createState() => _TodoAddingAdditionalRelationsState();
}



class _TodoAddingAdditionalRelationsState extends State<TodoAddingAdditionalRelationsWidget>{

  final _formKey = GlobalKey<FormState>();
  String dropdownRelationValue = 'None';
  String relatedTo ='';


  @override
  Widget build(BuildContext context) => AlertDialog(
    content: Form(
    key: _formKey,

    child: Column(
        mainAxisSize: MainAxisSize.min,
        children: [
        // The text header for the task card
        Text(
        'Adding additional relations',
        // text style
        style: TextStyle(
          fontWeight: FontWeight.bold,
          fontSize: 20,
          color: Colors.blueGrey,
        )
    ),

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
        height: 40.0,
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
          TodoRelatedToFormWidget(
              userRelatedTo: (relatedTo) => setState(() => this.relatedTo =  relatedTo),
              savedTodo: (){},
          ),


    ]
    ),
    ),
  );
}