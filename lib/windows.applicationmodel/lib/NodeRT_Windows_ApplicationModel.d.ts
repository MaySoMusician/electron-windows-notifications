declare module "windows.applicationmodel" {
  export class Size {
    constructor();
  }

  export class FullTrustAppContract {
    constructor();
  }

  export class StartupTaskContract {
    constructor();
  }

  export class PackageVersion {
    major: Number;
    minor: Number;
    build: Number;
    revision: Number;
    constructor();
  }

  export class PackageInstallProgress {
    percentComplete: Number;
    constructor();
  }

  export enum StartupTaskState {
    disabled,
    disabledByUser,
    enabled,
    disabledByPolicy,
    enabledByPolicy,
  }

  export enum PackageSignatureKind {
    none,
    developer,
    enterprise,
    store,
    system,
  }

  export enum AddResourcePackageOptions {
    none,
    forceTargetAppShutdown,
    applyUpdateIfAvailable,
  }

  export enum PackageContentGroupState {
    notStaged,
    queued,
    staging,
    staged,
  }

  export class FullTrustProcessLauncher {
    constructor();

    static launchFullTrustProcessForCurrentAppAsync(callback: (error: Error) => void): void ;
    static launchFullTrustProcessForCurrentAppAsync(parameterGroupId: String, callback: (error: Error) => void): void ;


    static launchFullTrustProcessForAppAsync(fullTrustPackageRelativeAppId: String, callback: (error: Error) => void): void ;
    static launchFullTrustProcessForAppAsync(fullTrustPackageRelativeAppId: String, parameterGroupId: String, callback: (error: Error) => void): void ;


  }

  export class StartupTask {
    state: StartupTaskState;
    taskId: String;
    constructor();

    static getForCurrentPackageAsync(callback: (error: Error, result: Object) => void): void ;


    static getAsync(taskId: String, callback: (error: Error, result: StartupTask) => void): void ;


    requestEnableAsync(callback: (error: Error, result: StartupTaskState) => void): void ;

    disable(): void;

  }

  export class AppDisplayInfo {
    description: String;
    displayName: String;
    constructor();

    getLogo(size: Object): Object;

  }

  export class AppInfo {
    appUserModelId: String;
    displayInfo: AppDisplayInfo;
    id: String;
    packageFamilyName: String;
    constructor();

  }

  export class PackageStatus {
    dataOffline: Boolean;
    dependencyIssue: Boolean;
    deploymentInProgress: Boolean;
    disabled: Boolean;
    licenseIssue: Boolean;
    modified: Boolean;
    needsRemediation: Boolean;
    notAvailable: Boolean;
    packageOffline: Boolean;
    servicing: Boolean;
    tampered: Boolean;
    isPartiallyStaged: Boolean;
    constructor();

    verifyIsOK(): Boolean;

  }

  export class PackageId {
    architecture: Number;
    familyName: String;
    fullName: String;
    name: String;
    publisher: String;
    publisherId: String;
    resourceId: String;
    version: PackageVersion;
    author: String;
    productId: String;
    constructor();

  }

  export class Package {
    static current: Package;
    dependencies: Object;
    id: PackageId;
    installedLocation: Object;
    isFramework: Boolean;
    description: String;
    displayName: String;
    isBundle: Boolean;
    isDevelopmentMode: Boolean;
    isResourcePackage: Boolean;
    logo: Object;
    publisherDisplayName: String;
    installedDate: Date;
    status: PackageStatus;
    isOptional: Boolean;
    signatureKind: PackageSignatureKind;
    installDate: Date;
    constructor();

    getAppListEntriesAsync(callback: (error: Error, result: Object) => void): void ;

    verifyContentIntegrityAsync(callback: (error: Error, result: Boolean) => void): void ;

    getContentGroupsAsync(callback: (error: Error, result: Object) => void): void ;

    getContentGroupAsync(name: String, callback: (error: Error, result: PackageContentGroup) => void): void ;

    stageContentGroupsAsync(names: Object, callback: (error: Error, result: Object) => void): void ;
    stageContentGroupsAsync(names: Object, moveToHeadOfQueue: Boolean, callback: (error: Error, result: Object) => void): void ;

    setInUseAsync(inUse: Boolean, callback: (error: Error, result: Boolean) => void): void ;

    getThumbnailToken(): String;

    launch(parameters: String): void;

  }

  export class PackageContentGroup {
    static requiredGroupName: String;
    isRequired: Boolean;
    name: String;
    package: Package;
    state: PackageContentGroupState;
    constructor();

  }

  export class PackageStagingEventArgs {
    activityId: String;
    errorCode: Number;
    isComplete: Boolean;
    package: Package;
    progress: Number;
    constructor();

  }

  export class PackageInstallingEventArgs {
    activityId: String;
    errorCode: Number;
    isComplete: Boolean;
    package: Package;
    progress: Number;
    constructor();

  }

  export class PackageUpdatingEventArgs {
    activityId: String;
    errorCode: Number;
    isComplete: Boolean;
    progress: Number;
    sourcePackage: Package;
    targetPackage: Package;
    constructor();

  }

  export class PackageUninstallingEventArgs {
    activityId: String;
    errorCode: Number;
    isComplete: Boolean;
    package: Package;
    progress: Number;
    constructor();

  }

  export class PackageStatusChangedEventArgs {
    package: Package;
    constructor();

  }

  export class PackageContentGroupStagingEventArgs {
    activityId: String;
    contentGroupName: String;
    errorCode: Number;
    isComplete: Boolean;
    isContentGroupRequired: Boolean;
    package: Package;
    progress: Number;
    constructor();

  }

  export class PackageCatalog {
    constructor();

    static openForCurrentPackage(): PackageCatalog;


    static openForCurrentUser(): PackageCatalog;


    addOptionalPackageAsync(optionalPackageFamilyName: String, callback: (error: Error, result: PackageCatalogAddOptionalPackageResult) => void): void ;

    removeOptionalPackagesAsync(optionalPackageFamilyNames: Object, callback: (error: Error, result: PackageCatalogRemoveOptionalPackagesResult) => void): void ;

    addResourcePackageAsync(resourcePackageFamilyName: String, resourceID: String, options: AddResourcePackageOptions, callback: (error: Error, result: PackageCatalogAddResourcePackageResult) => void): void ;

    removeResourcePackagesAsync(resourcePackages: Object, callback: (error: Error, result: PackageCatalogRemoveResourcePackagesResult) => void): void ;

    addListener(type: "PackageInstalling", listener: (ev: Event) => void): void ;
    removeListener(type: "PackageInstalling", listener: (ev: Event) => void): void ;
    on(type: "PackageInstalling", listener: (ev: Event) => void): void ;
    off(type: "PackageInstalling", listener: (ev: Event) => void): void ;
    
    addListener(type: "PackageStaging", listener: (ev: Event) => void): void ;
    removeListener(type: "PackageStaging", listener: (ev: Event) => void): void ;
    on(type: "PackageStaging", listener: (ev: Event) => void): void ;
    off(type: "PackageStaging", listener: (ev: Event) => void): void ;
    
    addListener(type: "PackageStatusChanged", listener: (ev: Event) => void): void ;
    removeListener(type: "PackageStatusChanged", listener: (ev: Event) => void): void ;
    on(type: "PackageStatusChanged", listener: (ev: Event) => void): void ;
    off(type: "PackageStatusChanged", listener: (ev: Event) => void): void ;
    
    addListener(type: "PackageUninstalling", listener: (ev: Event) => void): void ;
    removeListener(type: "PackageUninstalling", listener: (ev: Event) => void): void ;
    on(type: "PackageUninstalling", listener: (ev: Event) => void): void ;
    off(type: "PackageUninstalling", listener: (ev: Event) => void): void ;
    
    addListener(type: "PackageUpdating", listener: (ev: Event) => void): void ;
    removeListener(type: "PackageUpdating", listener: (ev: Event) => void): void ;
    on(type: "PackageUpdating", listener: (ev: Event) => void): void ;
    off(type: "PackageUpdating", listener: (ev: Event) => void): void ;
    
    addListener(type: "PackageContentGroupStaging", listener: (ev: Event) => void): void ;
    removeListener(type: "PackageContentGroupStaging", listener: (ev: Event) => void): void ;
    on(type: "PackageContentGroupStaging", listener: (ev: Event) => void): void ;
    off(type: "PackageContentGroupStaging", listener: (ev: Event) => void): void ;
    
    addListener(type: string, listener: (ev: Event) => void): void ;
    removeListener(type: string, listener: (ev: Event) => void): void ;
    on(type: string, listener: (ev: Event) => void): void ;
    off(type: string, listener: (ev: Event) => void): void ;
    

  }

  export class PackageCatalogAddOptionalPackageResult {
    extendedError: Number;
    package: Package;
    constructor();

  }

  export class PackageCatalogRemoveOptionalPackagesResult {
    extendedError: Number;
    packagesRemoved: Object;
    constructor();

  }

  export class PackageCatalogRemoveResourcePackagesResult {
    extendedError: Number;
    packagesRemoved: Object;
    constructor();

  }

  export class PackageCatalogAddResourcePackageResult {
    extendedError: Number;
    isComplete: Boolean;
    package: Package;
    constructor();

  }

  export class DesignMode {
    static designModeEnabled: Boolean;
    static designMode2Enabled: Boolean;
    constructor();

  }

  export class AppInstance {
    static recommendedInstance: AppInstance;
    isCurrentInstance: Boolean;
    key: String;
    constructor();

    static getActivatedEventArgs(): Object;


    static findOrRegisterInstanceForKey(key: String): AppInstance;


    static unregister(): void;


    static getInstances(): Object;


    redirectActivationTo(): void;

  }

  export class SuspendingEventArgs {
    suspendingOperation: SuspendingOperation;
    constructor();

  }

  export class LeavingBackgroundEventArgs {
    constructor();

    getDeferral(): Object;

  }

  export class EnteredBackgroundEventArgs {
    constructor();

    getDeferral(): Object;

  }

  export class ISuspendingDeferral {
    constructor();

    complete(): void;

  }

  export class SuspendingDeferral {
    constructor();

    complete(): void;

  }

  export class ISuspendingOperation {
    deadline: Date;
    constructor();

    getDeferral(): SuspendingDeferral;

  }

  export class SuspendingOperation {
    deadline: Date;
    constructor();

    getDeferral(): SuspendingDeferral;

  }

  export class ISuspendingEventArgs {
    suspendingOperation: SuspendingOperation;
    constructor();

  }

  export class ILeavingBackgroundEventArgs {
    constructor();

    getDeferral(): Object;

  }

  export class IEnteredBackgroundEventArgs {
    constructor();

    getDeferral(): Object;

  }

  export class CameraApplicationManager {
    constructor();

    static showInstalledApplicationsUI(): void;


  }

}



