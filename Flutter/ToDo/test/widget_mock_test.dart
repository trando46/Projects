/***
 * This class is to use the mock
 * https://pub.dev/packages/mockito
 */
import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:hw1/model/todo_model.dart';
import 'package:hw1/pages/home_page.dart';
import 'package:hw1/storage/storage.dart';
import 'package:hw1/widget/todo_completed_list_widget.dart';
import 'package:hw1/widget/todo_form_inputs_widget.dart';
import 'package:hw1/widget/todo_card_structure_widget.dart';
import 'package:hw1/widget/todo_has_relation_list_widget.dart';
import 'package:hw1/widget/todo_inprogress_list_widget.dart';
import 'package:hw1/widget/todo_open_list_widget.dart';

import 'package:hw1/main.dart';
import 'package:hw1/widget/todo_ui_homepage_layout_widget.dart';
import 'package:hw1/widget/todo_ui_individual_task_card_display_widget.dart';
import 'package:provider/provider.dart';

import 'package:mockito/mockito.dart';
import 'package:mockito/annotations.dart';
import 'widget_mock_test.mocks.dart';


class TodoModel {
  DateTime createdTime = DateTime.now();
  String title = 'Food';
  int? id = 1;
  String description = "Apple";
  bool isOpen = true;
  bool isInProgress = false;
  bool isComplete = false;
  bool hasRelation = false;
  String status = '';
  String relationType = '';
  String relatedTo = '';
  String imageFile = '';
}
@GenerateMocks([TodoModel])
void main(){
  late TodoModel todosMock;

  setUp((){
    todosMock = MockTodoModel();
  });

  test('Mock_Verify_Title',() {
    when(todosMock.title).thenReturn('Food');

    todosMock.title;

    verify(todosMock.title);
  });

  test('Mock_Verify_Description',() {
    when(todosMock.description).thenReturn('Apple');

    todosMock.description;

    verify(todosMock.description);
  });

  test('Mock_Stubbing_title',() {
    when(todosMock.title).thenReturn('Buy clothes');

    expect(todosMock.title, 'Buy clothes');
  });

  /**
   * Find one task card
   */
  testWidgets('Mock_Shows_One_Valid_task_Card_Widget_Should_Pass', (tester) async {
    when(todosMock.title).thenReturn('Buy clothes');

    expect(todosMock.title, 'Buy clothes');


    await tester.pumpWidget(MyApp());

    // Go to the form (The form will be the parent)
    await tester.tap(find.byIcon(Icons.add));
    await tester.pump();

    // expect to find the features of the form
    expect(find.text('Add Todo'), findsOneWidget);
    expect(find.text('Save'),findsOneWidget);
    expect(find.text('Exit'),findsOneWidget);

    // Filling out the form requires to call the Child class and once save it
    // will do a callback to the parent.
    await tester.enterText(find.byKey(Key('Title')), todosMock.title);
    await tester.tap(find.byKey(Key('Save')));
    await tester.pump();

    // exepect to only find the task card in homescreen
    expect(find.text(todosMock.title), findsOneWidget);

  });




}