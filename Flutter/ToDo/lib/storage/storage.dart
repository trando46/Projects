/**
 * HW1
 * Author: Bao Tran Tran Do
 * version 1.2
 * 1/22/2022
 */

import 'dart:math';

import 'package:cloud_firestore/cloud_firestore.dart';
import 'package:flutter/material.dart';
import 'package:hw1/database/todos_database.dart';
import 'package:hw1/model/todo_model.dart';
import 'package:hw1/database/todos_firebase.dart';
import 'dart:io';

/***
 * This class is temporary storage container for the todos.
 */
class TodosStorage extends ChangeNotifier{

  // The list to contain all of the todos (storage)
  List<TodoModel> _todos = [];

  // This makes the todos public and display: includes todos status: open,
  // inprogress, close
  List<TodoModel> get todos => _todos.toList();

  // This is contain all the opentask
  List<TodoModel> get todosIsOpen=> _todos.where((todo) => todo.status == 'Open').toList();

  // This is contain all the inProgres task
  List<TodoModel> get todosInProgress=> _todos.where((todo) => todo.status == 'In Progress').toList();

  // This is contain all the completed task
  List<TodoModel> get todosIsCompleted=> _todos.where((todo) => todo.status == 'Completed!!!').toList();

  // This contain todos with relationship
  List<TodoModel> get todosHasRelation => _todos.where((todo) => !todo.relatedTo.isEmpty && todo.relationType != 'None' && todo.relationType != '').toList();


  // Firebase
  // The list to contain all of the todos (storage)
  List<TodoModel> _firebaseTodo = [];

  // This makes the todos public and display: includes todos status: open,
  // inprogress, close
  List<TodoModel> get firebaseTodos => _firebaseTodo.toList();

  // This is contain all the opentask
  List<TodoModel> get firebaseTodosIsOpen=> _firebaseTodo.where((todo) => todo.status == 'Open').toList();

  // This is contain all the inProgres task
  List<TodoModel> get firebaseTodosInProgress=> _firebaseTodo.where((todo) => todo.status == 'In Progress').toList();

  // This is contain all the completed task
  List<TodoModel> get firebaseTodosIsCompleted=> _firebaseTodo.where((todo) => todo.status == 'Completed!!!').toList();

  // This contain todos with relationship
  List<TodoModel> get firebaseTodosHasRelation => _firebaseTodo.where((todo) => !todo.relatedTo.isEmpty && todo.relationType != 'None' && todo.relationType != '').toList();




  TodosStorage(){
    _getAllEntriesSQLDatabase();
    _getAllEntriesFirebase();
  }


  Future<void> _getAllEntriesSQLDatabase() async {
    final entries = await TodosDatabase.instance.getAll();
    _todos = entries;
    _todos.sort((a, b) => b.createdTime.compareTo(a.createdTime));
    notifyListeners();

  }

  Future<void> _getAllEntriesFirebase() async {
    final entries = await TodosFireBase.instance.getAll();
    _firebaseTodo= entries;
    _firebaseTodo.sort((a, b) => b.createdTime.compareTo(a.createdTime));
    notifyListeners();

  }


  /**
   * Adding the tasks to the firebase
   */
  void addTodoFirebase(TodoModel todo) async {
    _firebaseTodo.add(todo);
    TodosFireBase.instance.create(todo);
    _getAllEntriesFirebase();
  }

  /***
   * This function is for assigning a specific ID for the task card in the firebase
   */
  void idCounter(TodoModel todo){
    int intValue = Random().nextInt(100000);
    todo.id = intValue;
  }

  /**
   * Update the list of the todos from the list above
   */
  void updateFirebaseTodo(TodoModel todo, String title, String description, String relationType, String relatedTo, String fileName) {
    todo.title = title;
    todo.description = description;
    todo.createdTime = DateTime.now();
    todo.relationType = relationType;
    todo.relatedTo = relatedTo;
    todo.imageFile = fileName;
    TodosFireBase.instance.update(todo);
    _firebaseTodo.sort((a, b) => b.createdTime.compareTo(a.createdTime));
    notifyListeners();
  }


  /**
   * Add the list of the todos to the list above
   */
  void addTodoSQLDatabase(TodoModel todo){
    //_todos.add(todo);
    //_todos.sort((a, b) => b.createdTime.compareTo(a.createdTime));
    // This is for updating the UI
    //notifyListeners();
    _todos.add(todo);
    TodosDatabase.instance.create(todo);
    _getAllEntriesSQLDatabase();
    _todos.sort((a, b) => b.createdTime.compareTo(a.createdTime));
    notifyListeners();
  }



  /**
   * Update the list of the todos from the list above
   */
  void updateTodo(TodoModel todo, String title, String description, String relationType, String relatedTo, String fileName) {
    todo.title = title;
    todo.description = description;
    todo.createdTime = DateTime.now();
    todo.relationType = relationType;
    todo.relatedTo = relatedTo;
    todo.imageFile = fileName;
    TodosDatabase.instance.update(todo);
    _todos.sort((a, b) => b.createdTime.compareTo(a.createdTime));
    notifyListeners();
  }


  /**
   *  Mark the task card to be inprogress
   */
  bool toggleTodoInProgressStatus(TodoModel todo){
    todo.isInProgress = !todo.isInProgress;
    todo.status = 'In Progress';
    todo.createdTime = DateTime.now();
    TodosDatabase.instance.update(todo);
    _todos.sort((a, b) => b.createdTime.compareTo(a.createdTime));
    notifyListeners();
    return todo.isInProgress;
  }

  /**
   * Mark the task card to be completed
   */
  bool toggleTodoIsCompletedStatus(TodoModel todo){
    todo.isComplete = !todo.isComplete;
    todo.status = 'Completed!!!';
    todo.createdTime = DateTime.now();
    TodosDatabase.instance.update(todo);
    _todos.sort((a, b) => b.createdTime.compareTo(a.createdTime));
    notifyListeners();
    return todo.isComplete;
  }

  /**
   * Mark the task card to be completed
   */
  bool toggleTodoIsOpenStatus(TodoModel todo){
    todo.isOpen = !todo.isOpen;
    todo.status = 'Open';
    todo.createdTime = DateTime.now();
    TodosDatabase.instance.update(todo);
    _todos.sort((a, b) => b.createdTime.compareTo(a.createdTime));
    notifyListeners();
    return todo.isOpen;
  }

  /**
   * Mark the task card that has relation
   */
  bool toggleTodoHasRelationStatus(TodoModel todo){
    todo.hasRelation = !todo.hasRelation;
    todo.createdTime = DateTime.now();
    TodosDatabase.instance.update(todo);
    _todos.sort((a, b) => b.createdTime.compareTo(a.createdTime));
    notifyListeners();
    return todo.hasRelation;
  }

  /**
   * Remove the list of the todos to the list above
   */
  void removeTodo(TodoModel todo) {
    //_todos.remove(todo);
    //_todos.sort((a, b) => b.createdTime.compareTo(a.createdTime));
    //notifyListeners();
    _todos.remove(todo);
    TodosDatabase.instance.delete(todo);
    _getAllEntriesSQLDatabase();

    notifyListeners();
  }

  /**
   * Remove the list of the todos to the list above
   */
  void removeSharedTodo(TodoModel todo) {
    //_todos.remove(todo);
    //_todos.sort((a, b) => b.createdTime.compareTo(a.createdTime));
    //notifyListeners();
    _firebaseTodo.remove(todo);
    TodosFireBase.instance.delete(todo);
    _getAllEntriesFirebase();
    notifyListeners();
  }



  /**
   * Remove the list of the todos to the list above
   */
  void removeRelationTodo(TodoModel todo) {
    todo.relationType = '';
    todo.relatedTo = '';
    TodosDatabase.instance.update(todo);
    _todos.sort((a, b) => b.createdTime.compareTo(a.createdTime));
    notifyListeners();
  }

  /**
   * Remove the list of the todos to the list above
   */
  void removeRelationSharedTodo(TodoModel todo) {
    todo.relationType = '';
    todo.relatedTo = '';
    TodosFireBase.instance.update(todo);
    _firebaseTodo.sort((a, b) => b.createdTime.compareTo(a.createdTime));
    notifyListeners();
  }



  /**
   *  Mark the task card to be inprogress
   */
  bool toggleSharedTodoInProgressStatus(TodoModel todo){
    todo.isInProgress = !todo.isInProgress;
    todo.status = 'In Progress';
    todo.createdTime = DateTime.now();
    TodosFireBase.instance.update(todo);
    _firebaseTodo.sort((a, b) => b.createdTime.compareTo(a.createdTime));
    notifyListeners();
    return todo.isInProgress;
  }

  /**
   * Mark the task card to be completed
   */
  bool toggleSharedTodoIsCompletedStatus(TodoModel todo){
    todo.isComplete = !todo.isComplete;
    todo.status = 'Completed!!!';
    todo.createdTime = DateTime.now();
    TodosFireBase.instance.update(todo);
    _firebaseTodo.sort((a, b) => b.createdTime.compareTo(a.createdTime));
    notifyListeners();
    return todo.isComplete;
  }

  /**
   * Mark the task card to be completed
   */
  bool toggleSharedTodoIsOpenStatus(TodoModel todo){
    todo.isOpen = !todo.isOpen;
    todo.status = 'Open';
    todo.createdTime = DateTime.now();
    TodosFireBase.instance.update(todo);
    _firebaseTodo.sort((a, b) => b.createdTime.compareTo(a.createdTime));
    notifyListeners();
    return todo.isOpen;
  }

  /**
   * Mark the task card that has relation
   */
  bool toggleSharedTodoHasRelationStatus(TodoModel todo){
    todo.hasRelation = !todo.hasRelation;
    todo.createdTime = DateTime.now();
    TodosDatabase.instance.update(todo);
    _firebaseTodo.sort((a, b) => b.createdTime.compareTo(a.createdTime));
    notifyListeners();
    return todo.hasRelation;
  }



}