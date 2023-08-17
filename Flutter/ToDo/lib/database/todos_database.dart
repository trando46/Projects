import 'package:flutter/cupertino.dart';
import 'package:sqflite/sqflite.dart';
import 'package:hw1/model/todo_model.dart';

/**
 * DiaryDatabase is the local Sqlite.
 */
class TodosDatabase{

  static final TodosDatabase instance = TodosDatabase._init();

  //creating db.
  static Database? _database;

  //initializing db.
  TodosDatabase._init();


  Future<Database> get database async{
    //return database if it does not exist.
    if(_database != null) return _database!;

    //otherwise create new db.
    _database = await _initDB('todosDatabase.db');
    return _database!;
  }

  // Get the path
  Future<Database> _initDB(String filePath) async{
    final dbPath = await getDatabasesPath();
    final path = dbPath+filePath;
    return await openDatabase(path, version: 1, onCreate: _createDB);
  }

 // Create the schema
  Future _createDB(Database db, int version) async{
    final idType = "INTEGER PRIMARY KEY AUTOINCREMENT";
    final boolType = 'BOOLEAN NOT NULL';
    final textType = 'TEXT NOT NULL';

    await db.execute('''
      CREATE TABLE $todosTable(
        ${TodosFields.id} $idType, 
        ${TodosFields.createdTime} $textType,
        ${TodosFields.title} $textType,
        ${TodosFields.description} $textType,
        ${TodosFields.status} $textType,
        ${TodosFields.relationType} $textType,
        ${TodosFields.relatedTo} $textType,
        ${TodosFields.isOpen} $boolType, 
        ${TodosFields.isInProgress} $boolType, 
        ${TodosFields.isComplete} $boolType, 
        ${TodosFields.hasRelation} $boolType, 
        ${TodosFields.imageFile} $textType 
      )
    ''');
  }

  // Get all the items from the database
  Future<List<TodoModel>> getAll() async {
    final db = await instance.database;

    final allEntries = await db.query(todosTable);

    return allEntries.map((j) => TodoModel.fromJson(j)).toList();;
  }

 // Insert into the database
  Future create(TodoModel todos) async {
    final db = await instance.database;

    await db.insert(todosTable, todos.toJson());

  }

  // delete the item from the database
  Future delete(TodoModel todos) async {
    final db = await instance.database;

    var id = todos.id;

    await db.rawQuery("DELETE FROM $todosTable WHERE id = $id");
  }

  //update the item from the database.
  Future update(TodoModel todos) async {
    final db = await instance.database;

    return db.update(
      todosTable,
      todos.toJson(),
      where: '${TodosFields.id} = ?',
      whereArgs: [todos.id],
    );
  }


  Future close() async{
    final db = await instance.database;
    db.close(); //closes connection to database.
  }

}