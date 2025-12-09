# Configuration de l'export vers Google Sheets

## Étapes pour configurer l'export vers Google Sheets

### 1. Créer un projet Google Cloud

1. Allez sur [Google Cloud Console](https://console.cloud.google.com/)
2. Créez un nouveau projet ou sélectionnez un projet existant
3. Activez l'API Google Sheets :
   - Allez dans "APIs & Services" > "Library"
   - Recherchez "Google Sheets API"
   - Cliquez sur "Enable"

### 2. Créer des identifiants OAuth 2.0

1. Allez dans "APIs & Services" > "Credentials"
2. Cliquez sur "Create Credentials" > "OAuth client ID"
3. Configurez l'écran de consentement OAuth si nécessaire
4. Choisissez "Desktop app" comme type d'application
5. Donnez un nom à votre client OAuth
6. Téléchargez le fichier JSON des identifiants

### 3. Obtenir un token d'accès (Méthode simplifiée)

Pour une utilisation rapide, vous pouvez utiliser [OAuth 2.0 Playground](https://developers.google.com/oauthplayground/):

1. Allez sur https://developers.google.com/oauthplayground/
2. Dans la section "Step 1", cochez "Google Sheets API v4"
3. Cliquez sur "Authorize APIs"
4. Connectez-vous avec votre compte Google
5. Cliquez sur "Exchange authorization code for tokens"
6. Copiez le "Access token" qui apparaît
7. Collez ce token dans l'application lorsque vous exportez

### 4. Configuration dans le code (Optionnel)

Si vous voulez intégrer directement les identifiants dans le code, modifiez `googlesheetsexporter.cpp` :

```cpp
clientId("VOTRE_CLIENT_ID")
clientSecret("VOTRE_CLIENT_SECRET")
```

**Note de sécurité** : Pour une application de production, ne stockez jamais les identifiants directement dans le code. Utilisez des variables d'environnement ou un fichier de configuration sécurisé.

### 5. Utilisation

1. Cliquez sur le bouton "📊 EXPORTER GOOGLE SHEETS"
2. Entrez le nom de la feuille (par défaut: "Fournisseurs")
3. Si c'est la première fois, entrez votre token d'accès
4. Le token sera sauvegardé pour les prochaines utilisations
5. Un nouveau spreadsheet sera créé automatiquement
6. Les données seront exportées avec les en-têtes de colonnes

### Limitations

- Le token d'accès expire après 1 heure. Vous devrez le renouveler périodiquement.
- Pour une solution permanente, implémentez le flux OAuth 2.0 complet avec refresh token.

### Améliorations futures

- Implémentation complète du flux OAuth 2.0 avec refresh token
- Support pour exporter vers un spreadsheet existant
- Support pour plusieurs feuilles dans un même spreadsheet
- Interface graphique pour la configuration OAuth

