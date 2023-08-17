// Mocks generated by Mockito 5.3.2 from annotations
// in hw1/test/widget_mock_test.dart.
// Do not manually edit this file.

// ignore_for_file: no_leading_underscores_for_library_prefixes
import 'package:mockito/mockito.dart' as _i1;

import 'widget_mock_test.dart' as _i2;

// ignore_for_file: type=lint
// ignore_for_file: avoid_redundant_argument_values
// ignore_for_file: avoid_setters_without_getters
// ignore_for_file: comment_references
// ignore_for_file: implementation_imports
// ignore_for_file: invalid_use_of_visible_for_testing_member
// ignore_for_file: prefer_const_constructors
// ignore_for_file: unnecessary_parenthesis
// ignore_for_file: camel_case_types
// ignore_for_file: subtype_of_sealed_class

class _FakeDateTime_0 extends _i1.SmartFake implements DateTime {
  _FakeDateTime_0(
    Object parent,
    Invocation parentInvocation,
  ) : super(
          parent,
          parentInvocation,
        );
}

/// A class which mocks [TodoModel].
///
/// See the documentation for Mockito's code generation for more information.
class MockTodoModel extends _i1.Mock implements _i2.TodoModel {
  MockTodoModel() {
    _i1.throwOnMissingStub(this);
  }

  @override
  DateTime get createdTime => (super.noSuchMethod(
        Invocation.getter(#createdTime),
        returnValue: _FakeDateTime_0(
          this,
          Invocation.getter(#createdTime),
        ),
      ) as DateTime);
  @override
  set createdTime(DateTime? _createdTime) => super.noSuchMethod(
        Invocation.setter(
          #createdTime,
          _createdTime,
        ),
        returnValueForMissingStub: null,
      );
  @override
  String get title => (super.noSuchMethod(
        Invocation.getter(#title),
        returnValue: '',
      ) as String);
  @override
  set title(String? _title) => super.noSuchMethod(
        Invocation.setter(
          #title,
          _title,
        ),
        returnValueForMissingStub: null,
      );
  @override
  set id(int? _id) => super.noSuchMethod(
        Invocation.setter(
          #id,
          _id,
        ),
        returnValueForMissingStub: null,
      );
  @override
  String get description => (super.noSuchMethod(
        Invocation.getter(#description),
        returnValue: '',
      ) as String);
  @override
  set description(String? _description) => super.noSuchMethod(
        Invocation.setter(
          #description,
          _description,
        ),
        returnValueForMissingStub: null,
      );
  @override
  bool get isOpen => (super.noSuchMethod(
        Invocation.getter(#isOpen),
        returnValue: false,
      ) as bool);
  @override
  set isOpen(bool? _isOpen) => super.noSuchMethod(
        Invocation.setter(
          #isOpen,
          _isOpen,
        ),
        returnValueForMissingStub: null,
      );
  @override
  bool get isInProgress => (super.noSuchMethod(
        Invocation.getter(#isInProgress),
        returnValue: false,
      ) as bool);
  @override
  set isInProgress(bool? _isInProgress) => super.noSuchMethod(
        Invocation.setter(
          #isInProgress,
          _isInProgress,
        ),
        returnValueForMissingStub: null,
      );
  @override
  bool get isComplete => (super.noSuchMethod(
        Invocation.getter(#isComplete),
        returnValue: false,
      ) as bool);
  @override
  set isComplete(bool? _isComplete) => super.noSuchMethod(
        Invocation.setter(
          #isComplete,
          _isComplete,
        ),
        returnValueForMissingStub: null,
      );
  @override
  bool get hasRelation => (super.noSuchMethod(
        Invocation.getter(#hasRelation),
        returnValue: false,
      ) as bool);
  @override
  set hasRelation(bool? _hasRelation) => super.noSuchMethod(
        Invocation.setter(
          #hasRelation,
          _hasRelation,
        ),
        returnValueForMissingStub: null,
      );
  @override
  String get status => (super.noSuchMethod(
        Invocation.getter(#status),
        returnValue: '',
      ) as String);
  @override
  set status(String? _status) => super.noSuchMethod(
        Invocation.setter(
          #status,
          _status,
        ),
        returnValueForMissingStub: null,
      );
  @override
  String get relationType => (super.noSuchMethod(
        Invocation.getter(#relationType),
        returnValue: '',
      ) as String);
  @override
  set relationType(String? _relationType) => super.noSuchMethod(
        Invocation.setter(
          #relationType,
          _relationType,
        ),
        returnValueForMissingStub: null,
      );
  @override
  String get relatedTo => (super.noSuchMethod(
        Invocation.getter(#relatedTo),
        returnValue: '',
      ) as String);
  @override
  set relatedTo(String? _relatedTo) => super.noSuchMethod(
        Invocation.setter(
          #relatedTo,
          _relatedTo,
        ),
        returnValueForMissingStub: null,
      );
  @override
  String get imageFile => (super.noSuchMethod(
        Invocation.getter(#imageFile),
        returnValue: '',
      ) as String);
  @override
  set imageFile(String? _imageFile) => super.noSuchMethod(
        Invocation.setter(
          #imageFile,
          _imageFile,
        ),
        returnValueForMissingStub: null,
      );
}
