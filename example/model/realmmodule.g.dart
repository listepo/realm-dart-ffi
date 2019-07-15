
//@RealmModule
part of 'realmmodule.dart';


class RealmModuleGenerated extends RealmModule {
  static final RealmConfiguration _singleton = new RealmModuleGenerated._internal();

  factory RealmModuleGenerated() {
    return _singleton;
  }

  RealmModuleGenerated._internal() {
  }

  @override
  T newProxyInstance<T extends RealmModel> (T obj) {
    if (obj.runtimeType == Person) {
      return Person$Realm() as T;
    }
    if (obj.runtimeType == Dog) {
      return Dog$Realm() as T;
    }
    throw Exception("Unsupported type ${obj}");
  }
}