#include <QtCore/QtCore>

/**
 * @param settings QSettings instance.
 * @param obj      JSON object to write to.
 * @param err      Error stream.
 * @returns Non-zero if an error ocurred.
 */
int convertToObject(QSettings &settings, QJsonObject &obj, QTextStream &err) {
    for (const QString key : settings.childKeys()) {
        if (!key.size()) {
            // Assume invalid file
            return 1;
        }
        QVariant value = settings.value(key);
        switch (value.type()) {
        case QMetaType::QString:
            obj[key] = QJsonValue(value.toString());
            break;

        case QMetaType::QVariantMap:
        case QMetaType::QVariantList:
            obj[key] = value.toJsonValue();
            break;

        case QMetaType::QStringList:
            obj[key] =
                QJsonValue(QJsonArray::fromStringList(value.toStringList()));
            break;

        default:
            err << "Unhandled type: " << value.typeName()
                << QStringLiteral("\n");
            break;
        }
    }

    int ret = 0;
    for (const QString group : settings.childGroups()) {
        settings.beginGroup(group);
        QJsonObject groupObj;
        ret = convertToObject(settings, groupObj, err);
        if (ret != 0) {
            // Assume invalid file
            return ret;
        }
        obj[group] = QJsonValue(groupObj);
        settings.endGroup();
    }

    return ret;
}

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
