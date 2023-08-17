/**
 * HW1
 * Author: Bao Tran Tran Do
 * version 1.2
 * 1/22/2022
 */

import 'dart:io';

class TodoModel {
  DateTime createdTime;
  String title;
  int? id;
  String description;
  bool isOpen;
  bool isInProgress;
  bool isComplete;
  bool hasRelation;
  String status;
  String relationType;
  String relatedTo;
  //List<String> relationType =[];
  String imageFile;
  bool firebase;

  // Create the constructor
  TodoModel({
    required this.createdTime,
    required this.title,
    this.status = '',
    this.description ='',
    this.id,
    this.isOpen = true,
    this.isComplete = false,
    this.isInProgress = false,
    this.hasRelation = false,
    this.relationType = '',
    this.relatedTo = '',
    this.imageFile = '',
    this.firebase = false,
  });

  //mapping the fields to the database
  Map<String, Object?> toJson() => {
    TodosFields.id: id,
    TodosFields.title: title,
    TodosFields.description: description,
    TodosFields.createdTime:createdTime.toIso8601String(),
    TodosFields.isOpen: isOpen ? 1 : 0,
    TodosFields.isInProgress: isInProgress ? 1 : 0,
    TodosFields.isComplete: isComplete ? 1 : 0,
    TodosFields.hasRelation: hasRelation? 1 : 0,
    TodosFields.status: status,
    TodosFields.relatedTo: relatedTo,
    TodosFields.relationType: relationType,
    TodosFields.imageFile: imageFile.toString(),
  };

  //reading the fields
  static TodoModel fromJson(Map<String, Object?> json) => TodoModel(
    id: json[TodosFields.id] as int,
    title: json[TodosFields.title].toString(),
    description: json[TodosFields.description].toString(),
    createdTime: DateTime.parse(json[TodosFields.createdTime].toString()),
    isOpen: json[TodosFields.isOpen] == 1,
    isInProgress: json[TodosFields.isInProgress] == 1,
    isComplete: json[TodosFields.isComplete] == 1,
    hasRelation: json[TodosFields.hasRelation] == 1,
    status: json[TodosFields.status].toString(),
    relatedTo: json[TodosFields.relatedTo].toString(),
    relationType: json[TodosFields.relationType].toString(),
    imageFile: json[TodosFields.imageFile].toString(),


  );

  //reading the fields
  static TodoModel fromJsonFirebase(Map<String?, dynamic?> json) => TodoModel(
    id: json[TodosFields.id] ,
    title: json[TodosFields.title] ,
    description: json[TodosFields.description],
    createdTime: DateTime.parse(json[TodosFields.createdTime]),
    isOpen: json[TodosFields.isOpen],
    isInProgress: json[TodosFields.isInProgress],
    isComplete: json[TodosFields.isComplete],
    hasRelation: json[TodosFields.hasRelation],
    status: json[TodosFields.status],
    relatedTo: json[TodosFields.relatedTo],
    relationType: json[TodosFields.relationType],
    imageFile: json[TodosFields.imageFile],


  );

  //mapping the fields to the database
  Map<String, Object?> toJsonFirebase() => {
    TodosFields.id: id,
    TodosFields.title: title,
    TodosFields.description: description,
    TodosFields.createdTime:createdTime.toIso8601String(),
    TodosFields.isOpen: isOpen ,
    TodosFields.isInProgress: isInProgress,
    TodosFields.isComplete: isComplete ,
    TodosFields.hasRelation: hasRelation,
    TodosFields.status: status,
    TodosFields.relatedTo: relatedTo,
    TodosFields.relationType: relationType,
    TodosFields.imageFile: imageFile.toString(),

  };

}

//name of the table
final String todosTable = 'todosTable';

// The fields stored in the database
class TodosFields{
  static final String createdTime = 'time';
  static final String title = 'title';
  static final String id = 'id';
  static final String description = 'description';
  static final String isOpen = 'isOpen';
  static final String isInProgress = 'isInProgress';
  static final String isComplete = 'isComplete';
  static final String hasRelation = 'hasRelation';
  static final String status = 'status';
  static final String relationType = 'relationType';
  static final String relatedTo = 'relatedTo';
  static final String imageFile = 'imageFile';
  static final String firebase = 'firebase';

  static final List<String> values = [
    // add all the fields into the list
    createdTime, title, id, description, isOpen, isInProgress, isComplete,
    hasRelation, status, relationType, relatedTo, imageFile, firebase
  ];
}