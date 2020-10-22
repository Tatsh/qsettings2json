#include <QtCore>

int convertToObject(QSettings &settings, QJsonObject &obj, QTextStream &err) {
    for (const QString key : settings.childKeys()) {
        if (!key.size()) {
            // Invalid document
            return 1;
        }
        QVariant value = settings.value(key);
        QString typeName = QLatin1String(QByteArray(value.typeName()));
        if (typeName == QStringLiteral("QString")) {
            obj[key] = QJsonValue(value.toString());
        } else if (typeName == QStringLiteral("QVariantMap") ||
                   typeName == QStringLiteral("QVariantList")) {
            obj[key] = value.toJsonValue();
        } else if (typeName == QStringLiteral("QStringList")) {
            obj[key] =
                QJsonValue(QJsonArray::fromStringList(value.toStringList()));
        } else {
            err << "Unhandled type: " << typeName << QStringLiteral("\n");
        }
    }

    int ret = 0;
    for (const QString group : settings.childGroups()) {
        settings.beginGroup(group);
        QJsonObject groupObj;
        ret = convertToObject(settings, groupObj, err);
        if (ret != 0) {
            return ret;
        }
        obj[group] = QJsonValue(groupObj);
        settings.endGroup();
    }

    return ret;
}

/**
 * It just so happens QSettings can read the Quassel IRC server configuration
 * file, even though Quassel uses its own Settings class.
 */
int main(__attribute__((unused)) int argc, char *argv[]) {
    QJsonObject obj;
    QString arg = QString::fromUtf8(argv[1]);
    QTextStream out(stdout);
    QTextStream err(stderr);
    QSettings settings(arg, QSettings::IniFormat);
    if (settings.status() != QSettings::NoError) {
        err << QStringLiteral("Incompatible file: ") << arg
            << QStringLiteral("\n");
        return 1;
    }
    int ret = convertToObject(settings, obj, err);
    if (!ret) {
        out << QJsonDocument(obj).toJson(QJsonDocument::Compact)
            << QStringLiteral("\n");
    } else {
        err << QStringLiteral("Incompatible file: ") << arg
            << QStringLiteral("\n");
    }
    return ret;
}
