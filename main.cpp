#include <QtCore>

/**
 * It just so happens QSettings can read the Quassel IRC server configuration
 * file, even though Quassel uses its own Settings class.
 */
int main(__attribute__((unused)) int argc, char *argv[]) {
    QTextStream out(stdout);
    QSettings settings(QString::fromUtf8(argv[1]), QSettings::IniFormat);
    for (const QString &key : settings.allKeys()) {
        out << key << QStringLiteral("=");
        QVariant value = settings.value(key);
        out << (QLatin1String(QByteArray(value.typeName())) ==
                        QStringLiteral("QVariantMap") ?
                    QString::fromUtf8(QJsonDocument::fromVariant(value).toJson(
                        QJsonDocument::Compact)) :
                    value.toString())
            << QStringLiteral("\n");
    }
    return 0;
}
