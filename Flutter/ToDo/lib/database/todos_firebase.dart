import 'package:hw1/model/todo_model.dart';
import 'package:cloud_firestore/cloud_firestore.dart';


/**
 * Todos for Firebase
 */
class TodosFireBase {
  //initializing db.
  TodosFireBase ._init();
  static final TodosFireBase instance = TodosFireBase._init();

  FirebaseFirestore db = FirebaseFirestore.instance;


  //create an item to be inserted into the database
  Future<void> create(TodoModel todos) async {
    final task = db.collection("todosShared").doc(todos.id.toString());
    final toJsonTask = todos.toJsonFirebase();
    await task.set(toJsonTask).then((value) => print("Successfully created!"),
        onError: (e) => print("[ERROR] $e"));
  }

  //update the item from the database
  Future<void> update(TodoModel todos) async {
    final toJsonTask = todos.toJsonFirebase();
    final task = db.collection("todosShared");
    task.doc(todos.id.toString())
        .update({"description": todos.description,
                 "hasRelation": todos.hasRelation,
      "imageFile": todos.imageFile,
      "isComplete": todos.isComplete,
      "isInProgress": todos.isInProgress,
      "isOpen": todos.isOpen,
      "relatedTo": todos.relatedTo,
      "relationType": todos.relationType,
      "status": todos.status,
      "time": todos.createdTime.toString(),
      "title": todos.title,
        })
        .then((_) => print('Updated'))
        .catchError((e) => print('Update failed: $e'));
  }

  // delete the item from the database
  Future<void> delete(TodoModel todos) async {
    final task = db.collection("todosShared").doc(todos.id.toString());
    await task.delete().then((value) => print("Successfully deleted!"),
        onError: (e) => print("[ERROR] $e"));
  }

  // Get all the items from the firebase
  Future<List<TodoModel>> getAll() async {
    final collection = db.collection("todosShared");

    final snapshot = await collection.get();
    return snapshot.docs.map((j) => TodoModel.fromJsonFirebase(j.data())).toList();
  }
  
}


