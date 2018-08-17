  
Size = (function () {
  var cls = function Size() {
    };
  return cls;
}) ();
exports.Size = Size;


  
FullTrustAppContract = (function () {
  var cls = function FullTrustAppContract() {
    };
  return cls;
}) ();
exports.FullTrustAppContract = FullTrustAppContract;


  
StartupTaskContract = (function () {
  var cls = function StartupTaskContract() {
    };
  return cls;
}) ();
exports.StartupTaskContract = StartupTaskContract;


  
PackageVersion = (function () {
  var cls = function PackageVersion() {
      this.major = new Number();
      this.minor = new Number();
      this.build = new Number();
      this.revision = new Number();
    };
  return cls;
}) ();
exports.PackageVersion = PackageVersion;


  
PackageInstallProgress = (function () {
  var cls = function PackageInstallProgress() {
      this.percentComplete = new Number();
    };
  return cls;
}) ();
exports.PackageInstallProgress = PackageInstallProgress;


_StartupTaskState = function () {
  this.disabled = 0;
  this.disabledByUser = 1;
  this.enabled = 2;
  this.disabledByPolicy = 3;
  this.enabledByPolicy = 4;
}
exports.StartupTaskState = new _StartupTaskState();

_PackageSignatureKind = function () {
  this.none = 0;
  this.developer = 1;
  this.enterprise = 2;
  this.store = 3;
  this.system = 4;
}
exports.PackageSignatureKind = new _PackageSignatureKind();

_AddResourcePackageOptions = function () {
  this.none = 0;
  this.forceTargetAppShutdown = 1;
  this.applyUpdateIfAvailable = 2;
}
exports.AddResourcePackageOptions = new _AddResourcePackageOptions();

_PackageContentGroupState = function () {
  this.notStaged = 0;
  this.queued = 1;
  this.staging = 2;
  this.staged = 3;
}
exports.PackageContentGroupState = new _PackageContentGroupState();

FullTrustProcessLauncher = (function () {
  var cls = function FullTrustProcessLauncher() {
  };
  

  cls.launchFullTrustProcessForCurrentAppAsync = function launchFullTrustProcessForCurrentAppAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }

cls.launchFullTrustProcessForCurrentAppAsync = function launchFullTrustProcessForCurrentAppAsync(parameterGroupId, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="parameterGroupId" type="String">A param.</param>
    /// </signature>
  }



  cls.launchFullTrustProcessForAppAsync = function launchFullTrustProcessForAppAsync(fullTrustPackageRelativeAppId, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="fullTrustPackageRelativeAppId" type="String">A param.</param>
    /// </signature>
  }

cls.launchFullTrustProcessForAppAsync = function launchFullTrustProcessForAppAsync(fullTrustPackageRelativeAppId, parameterGroupId, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="fullTrustPackageRelativeAppId" type="String">A param.</param>
    /// <param name="parameterGroupId" type="String">A param.</param>
    /// </signature>
  }



  return cls;
}) ();
exports.FullTrustProcessLauncher = FullTrustProcessLauncher;

StartupTask = (function () {
  var cls = function StartupTask() {
    this.state = new StartupTaskState();
    this.taskId = new String();
  };
  

  cls.prototype.requestEnableAsync = function requestEnableAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.disable = function disable() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.getForCurrentPackageAsync = function getForCurrentPackageAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }



  cls.getAsync = function getAsync(taskId, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="taskId" type="String">A param.</param>
    /// </signature>
  }



  return cls;
}) ();
exports.StartupTask = StartupTask;

AppDisplayInfo = (function () {
  var cls = function AppDisplayInfo() {
    this.description = new String();
    this.displayName = new String();
  };
  

  cls.prototype.getLogo = function getLogo(size) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="size" type="Object">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  return cls;
}) ();
exports.AppDisplayInfo = AppDisplayInfo;

AppInfo = (function () {
  var cls = function AppInfo() {
    this.appUserModelId = new String();
    this.displayInfo = new AppDisplayInfo();
    this.id = new String();
    this.packageFamilyName = new String();
  };
  

  return cls;
}) ();
exports.AppInfo = AppInfo;

PackageStatus = (function () {
  var cls = function PackageStatus() {
    this.dataOffline = new Boolean();
    this.dependencyIssue = new Boolean();
    this.deploymentInProgress = new Boolean();
    this.disabled = new Boolean();
    this.licenseIssue = new Boolean();
    this.modified = new Boolean();
    this.needsRemediation = new Boolean();
    this.notAvailable = new Boolean();
    this.packageOffline = new Boolean();
    this.servicing = new Boolean();
    this.tampered = new Boolean();
    this.isPartiallyStaged = new Boolean();
  };
  

  cls.prototype.verifyIsOK = function verifyIsOK() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  }


  return cls;
}) ();
exports.PackageStatus = PackageStatus;

PackageId = (function () {
  var cls = function PackageId() {
    this.architecture = new Number();
    this.familyName = new String();
    this.fullName = new String();
    this.name = new String();
    this.publisher = new String();
    this.publisherId = new String();
    this.resourceId = new String();
    this.version = new PackageVersion();
    this.author = new String();
    this.productId = new String();
  };
  

  return cls;
}) ();
exports.PackageId = PackageId;

Package = (function () {
  var cls = function Package() {
    this.dependencies = new Object();
    this.id = new PackageId();
    this.installedLocation = new Object();
    this.isFramework = new Boolean();
    this.description = new String();
    this.displayName = new String();
    this.isBundle = new Boolean();
    this.isDevelopmentMode = new Boolean();
    this.isResourcePackage = new Boolean();
    this.logo = new Object();
    this.publisherDisplayName = new String();
    this.installedDate = new Date();
    this.status = new PackageStatus();
    this.isOptional = new Boolean();
    this.signatureKind = new PackageSignatureKind();
    this.installDate = new Date();
  };
  

  cls.prototype.getAppListEntriesAsync = function getAppListEntriesAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.verifyContentIntegrityAsync = function verifyContentIntegrityAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.getContentGroupsAsync = function getContentGroupsAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.getContentGroupAsync = function getContentGroupAsync(name, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="name" type="String">A param.</param>
    /// </signature>
  }


  cls.prototype.stageContentGroupsAsync = function stageContentGroupsAsync(names, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="names" type="Object">A param.</param>
    /// </signature>
  }

cls.prototype.stageContentGroupsAsync = function stageContentGroupsAsync(names, moveToHeadOfQueue, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="names" type="Object">A param.</param>
    /// <param name="moveToHeadOfQueue" type="Boolean">A param.</param>
    /// </signature>
  }


  cls.prototype.setInUseAsync = function setInUseAsync(inUse, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="inUse" type="Boolean">A param.</param>
    /// </signature>
  }


  cls.prototype.getThumbnailToken = function getThumbnailToken() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.launch = function launch(parameters) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="parameters" type="String">A param.</param>
    /// </signature>
  }


  cls.current = new Package();
  return cls;
}) ();
exports.Package = Package;

PackageContentGroup = (function () {
  var cls = function PackageContentGroup() {
    this.isRequired = new Boolean();
    this.name = new String();
    this.package = new Package();
    this.state = new PackageContentGroupState();
  };
  

  cls.requiredGroupName = new String();
  return cls;
}) ();
exports.PackageContentGroup = PackageContentGroup;

PackageStagingEventArgs = (function () {
  var cls = function PackageStagingEventArgs() {
    this.activityId = new String();
    this.errorCode = new Number();
    this.isComplete = new Boolean();
    this.package = new Package();
    this.progress = new Number();
  };
  

  return cls;
}) ();
exports.PackageStagingEventArgs = PackageStagingEventArgs;

PackageInstallingEventArgs = (function () {
  var cls = function PackageInstallingEventArgs() {
    this.activityId = new String();
    this.errorCode = new Number();
    this.isComplete = new Boolean();
    this.package = new Package();
    this.progress = new Number();
  };
  

  return cls;
}) ();
exports.PackageInstallingEventArgs = PackageInstallingEventArgs;

PackageUpdatingEventArgs = (function () {
  var cls = function PackageUpdatingEventArgs() {
    this.activityId = new String();
    this.errorCode = new Number();
    this.isComplete = new Boolean();
    this.progress = new Number();
    this.sourcePackage = new Package();
    this.targetPackage = new Package();
  };
  

  return cls;
}) ();
exports.PackageUpdatingEventArgs = PackageUpdatingEventArgs;

PackageUninstallingEventArgs = (function () {
  var cls = function PackageUninstallingEventArgs() {
    this.activityId = new String();
    this.errorCode = new Number();
    this.isComplete = new Boolean();
    this.package = new Package();
    this.progress = new Number();
  };
  

  return cls;
}) ();
exports.PackageUninstallingEventArgs = PackageUninstallingEventArgs;

PackageStatusChangedEventArgs = (function () {
  var cls = function PackageStatusChangedEventArgs() {
    this.package = new Package();
  };
  

  return cls;
}) ();
exports.PackageStatusChangedEventArgs = PackageStatusChangedEventArgs;

PackageContentGroupStagingEventArgs = (function () {
  var cls = function PackageContentGroupStagingEventArgs() {
    this.activityId = new String();
    this.contentGroupName = new String();
    this.errorCode = new Number();
    this.isComplete = new Boolean();
    this.isContentGroupRequired = new Boolean();
    this.package = new Package();
    this.progress = new Number();
  };
  

  return cls;
}) ();
exports.PackageContentGroupStagingEventArgs = PackageContentGroupStagingEventArgs;

PackageCatalog = (function () {
  var cls = function PackageCatalog() {
  };
  

  cls.prototype.addOptionalPackageAsync = function addOptionalPackageAsync(optionalPackageFamilyName, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="optionalPackageFamilyName" type="String">A param.</param>
    /// </signature>
  }


  cls.prototype.removeOptionalPackagesAsync = function removeOptionalPackagesAsync(optionalPackageFamilyNames, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="optionalPackageFamilyNames" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.addResourcePackageAsync = function addResourcePackageAsync(resourcePackageFamilyName, resourceID, options, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="resourcePackageFamilyName" type="String">A param.</param>
    /// <param name="resourceID" type="String">A param.</param>
    /// <param name="options" type="AddResourcePackageOptions">A param.</param>
    /// </signature>
  }


  cls.prototype.removeResourcePackagesAsync = function removeResourcePackagesAsync(resourcePackages, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="resourcePackages" type="Object">A param.</param>
    /// </signature>
  }


  cls.openForCurrentPackage = function openForCurrentPackage() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="PackageCatalog" />
    /// </signature>
    return new PackageCatalog();
  }


  cls.openForCurrentUser = function openForCurrentUser() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="PackageCatalog" />
    /// </signature>
    return new PackageCatalog();
  }


    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.PackageCatalog = PackageCatalog;

PackageCatalogAddOptionalPackageResult = (function () {
  var cls = function PackageCatalogAddOptionalPackageResult() {
    this.extendedError = new Number();
    this.package = new Package();
  };
  

  return cls;
}) ();
exports.PackageCatalogAddOptionalPackageResult = PackageCatalogAddOptionalPackageResult;

PackageCatalogRemoveOptionalPackagesResult = (function () {
  var cls = function PackageCatalogRemoveOptionalPackagesResult() {
    this.extendedError = new Number();
    this.packagesRemoved = new Object();
  };
  

  return cls;
}) ();
exports.PackageCatalogRemoveOptionalPackagesResult = PackageCatalogRemoveOptionalPackagesResult;

PackageCatalogRemoveResourcePackagesResult = (function () {
  var cls = function PackageCatalogRemoveResourcePackagesResult() {
    this.extendedError = new Number();
    this.packagesRemoved = new Object();
  };
  

  return cls;
}) ();
exports.PackageCatalogRemoveResourcePackagesResult = PackageCatalogRemoveResourcePackagesResult;

PackageCatalogAddResourcePackageResult = (function () {
  var cls = function PackageCatalogAddResourcePackageResult() {
    this.extendedError = new Number();
    this.isComplete = new Boolean();
    this.package = new Package();
  };
  

  return cls;
}) ();
exports.PackageCatalogAddResourcePackageResult = PackageCatalogAddResourcePackageResult;

DesignMode = (function () {
  var cls = function DesignMode() {
  };
  

  cls.designModeEnabled = new Boolean();
  cls.designMode2Enabled = new Boolean();
  return cls;
}) ();
exports.DesignMode = DesignMode;

AppInstance = (function () {
  var cls = function AppInstance() {
    this.isCurrentInstance = new Boolean();
    this.key = new String();
  };
  

  cls.prototype.redirectActivationTo = function redirectActivationTo() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.getActivatedEventArgs = function getActivatedEventArgs() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.findOrRegisterInstanceForKey = function findOrRegisterInstanceForKey(key) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="key" type="String">A param.</param>
    /// <returns type="AppInstance" />
    /// </signature>
    return new AppInstance();
  }


  cls.unregister = function unregister() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.getInstances = function getInstances() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.recommendedInstance = new AppInstance();
  return cls;
}) ();
exports.AppInstance = AppInstance;

SuspendingEventArgs = (function () {
  var cls = function SuspendingEventArgs() {
    this.suspendingOperation = new SuspendingOperation();
  };
  

  return cls;
}) ();
exports.SuspendingEventArgs = SuspendingEventArgs;

LeavingBackgroundEventArgs = (function () {
  var cls = function LeavingBackgroundEventArgs() {
  };
  

  cls.prototype.getDeferral = function getDeferral() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  return cls;
}) ();
exports.LeavingBackgroundEventArgs = LeavingBackgroundEventArgs;

EnteredBackgroundEventArgs = (function () {
  var cls = function EnteredBackgroundEventArgs() {
  };
  

  cls.prototype.getDeferral = function getDeferral() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  return cls;
}) ();
exports.EnteredBackgroundEventArgs = EnteredBackgroundEventArgs;

ISuspendingDeferral = (function () {
  var cls = function ISuspendingDeferral() {
  };
  

  cls.prototype.complete = function complete() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  return cls;
}) ();
exports.ISuspendingDeferral = ISuspendingDeferral;

SuspendingDeferral = (function () {
  var cls = function SuspendingDeferral() {
  };
  

  cls.prototype.complete = function complete() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  return cls;
}) ();
exports.SuspendingDeferral = SuspendingDeferral;

ISuspendingOperation = (function () {
  var cls = function ISuspendingOperation() {
    this.deadline = new Date();
  };
  

  cls.prototype.getDeferral = function getDeferral() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="SuspendingDeferral" />
    /// </signature>
    return new SuspendingDeferral();
  }


  return cls;
}) ();
exports.ISuspendingOperation = ISuspendingOperation;

SuspendingOperation = (function () {
  var cls = function SuspendingOperation() {
    this.deadline = new Date();
  };
  

  cls.prototype.getDeferral = function getDeferral() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="SuspendingDeferral" />
    /// </signature>
    return new SuspendingDeferral();
  }


  return cls;
}) ();
exports.SuspendingOperation = SuspendingOperation;

ISuspendingEventArgs = (function () {
  var cls = function ISuspendingEventArgs() {
    this.suspendingOperation = new SuspendingOperation();
  };
  

  return cls;
}) ();
exports.ISuspendingEventArgs = ISuspendingEventArgs;

ILeavingBackgroundEventArgs = (function () {
  var cls = function ILeavingBackgroundEventArgs() {
  };
  

  cls.prototype.getDeferral = function getDeferral() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  return cls;
}) ();
exports.ILeavingBackgroundEventArgs = ILeavingBackgroundEventArgs;

IEnteredBackgroundEventArgs = (function () {
  var cls = function IEnteredBackgroundEventArgs() {
  };
  

  cls.prototype.getDeferral = function getDeferral() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  return cls;
}) ();
exports.IEnteredBackgroundEventArgs = IEnteredBackgroundEventArgs;

CameraApplicationManager = (function () {
  var cls = function CameraApplicationManager() {
  };
  

  cls.showInstalledApplicationsUI = function showInstalledApplicationsUI() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  return cls;
}) ();
exports.CameraApplicationManager = CameraApplicationManager;

