import 'package:realm/src/dart/realm_configuration.dart';
import 'package:realm/src/dart/realm_model.dart';
import 'package:realm/src/dart/realm_results.dart';
import 'package:realm/test/constants.dart';
// import 'package:realm/src/dart/realm_schema.dart';

import 'dog.dart';
part 'realm_module.g.dart'; 

// @RealmSchema("/Users/Nabil/Dev/realm/realm-dart-ffi/test.realm" , [Dog, Person])//TODO this might be a bug reproduce in an isolated example then create an issue
// class RealmModule {
  
// }

// @RealmSchema
class RealmModule extends RealmConfiguration {
  @override
  String path() {
    return realm_test_directory + "test.realm";
  }

  @override
  List<RealmModel> schema() {
    return [Dog()];
  }

}