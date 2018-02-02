#ifndef __ZPROPERTYIDS_H__
#define __ZPROPERTYIDS_H__

/////////////////////////////////////////////////////////////////////////////
//
//@flag ZS_BP_PROP_BASIC | <c ZBBPBasicProperty> property that contains process values
//
//@flag ZS_BP_PROP_PROCESS | <c ZBBPProcessProperty> property that contains process values
//
//@flag ZS_BP_PROP_PROCEDURE | <c ZBBPProcedureProperty> property that contains procedure values
//
//@flag ZS_BP_PROP_DELIVERABLE | <c ZBBPDeliverableProperty> property that contains deliverable values
//
//@flag ZS_BP_PROP_PAGE | <c ZBBPPageProperty> property that contains page values
//
//@flag ZS_BP_PROP_DOOR | <c ZBBPDoorProperty> property that contains door values
//
//@flag ZS_BP_PROP_START | <c ZBBPStartProperty> property that contains start values
//
//@flag ZS_BP_PROP_STOP | <c ZBBPStopProperty> property that contains stop values
//
//@flag ZS_BP_PROP_DOCUMENTATION | <c ZBBPDocumentationProperty> property that contains documentation values
//
//@flag ZS_BP_PROP_COST | <c ZBBPCostProperty> property that contains cost values
//
//@flag ZS_BP_PROP_DELIVERABLE_COST | <c ZBBPCostPropertiesDeliverable> property that contains cost values
//
//@flag ZS_BP_PROP_PROCEDURE_COST | <c ZBBPCostPropertiesDeliverable> property that contains cost values
//
//@flag ZS_BP_PROP_EXTFILE | <c ZBBPFormProperty> property that contains cost values
//
//@flag ZS_BP_PROP_MODEL_BASIC | <c ZBBPBasicModelProperty> property that contains process values
//
//@flag ZS_BP_PROP_UNIT | <c ZBBPUnitProperties> property that contains process values
//
//@flag ZS_BP_PROP_QUANTITY | <c ZBBPBasicModelProperty> property that contains process values
//
//@flag ZS_BP_PROP_COMBINATION | <c ZBBPCombinationProperties> property that contains combination
//
//@flag ZS_BP_PROP_SIM_DELIVERABLE | <c ZBBPSimPropertiesDeliverable> property that contains combination
//
//@flag ZS_BP_PROP_SIM_PROCEDURE | <c ZBBPSimPropertiesProcedure> property that contains combination
//
//@flag ZS_BP_PROP_SIM_PROCESS | <c ZBBPSimPropertiesProcess> property that contains combination
//
//@flag ZS_BP_PROP_TASKLIST | <c ZBBPTaskListProperties> property that contains combination
//
//@flag ZS_BP_PROP_DECISIONLIST | <c ZBBPDecisionListProperties> property that contains combination
//
//@flag ZS_BP_PROP_TEXTITEMLIST | <c ZBBPTextItemListProperties> property that contains combination
//
//@flag ZS_BP_PROP_EXTAPP | <c ZBExtAppProperties> property that contains combination
//
//@flag ZS_BP_PROP_LANGUAGE | <c ZBLanguageProp> property that contains the language
//
//@flag ZS_BP_PROP_PRESTATIONS | <c ZBBPPrestationNode> property that contains prestation

#define ZPROP_CUSTOM_PROPERTY_BASE				0x10000

#define ZS_BP_PROP_BASIC						(ZPROP_CUSTOM_PROPERTY_BASE + 20)
#define ZS_BP_PROP_PROCESS						(ZPROP_CUSTOM_PROPERTY_BASE + 40)
#define ZS_BP_PROP_PROCEDURE					(ZPROP_CUSTOM_PROPERTY_BASE + 60)
#define ZS_BP_PROP_DELIVERABLE					(ZPROP_CUSTOM_PROPERTY_BASE + 80)
#define ZS_BP_PROP_PAGE							(ZPROP_CUSTOM_PROPERTY_BASE + 100)
#define ZS_BP_PROP_DOOR							(ZPROP_CUSTOM_PROPERTY_BASE + 120)
#define ZS_BP_PROP_START						(ZPROP_CUSTOM_PROPERTY_BASE + 140)
#define ZS_BP_PROP_STOP							(ZPROP_CUSTOM_PROPERTY_BASE + 160)
#define ZS_BP_PROP_DOCUMENTATION				(ZPROP_CUSTOM_PROPERTY_BASE + 180)
#define ZS_BP_PROP_COST							(ZPROP_CUSTOM_PROPERTY_BASE + 200)
#define ZS_BP_PROP_DELIVERABLE_COST				(ZPROP_CUSTOM_PROPERTY_BASE + 240)
#define ZS_BP_PROP_PROCEDURE_COST				(ZPROP_CUSTOM_PROPERTY_BASE + 280)
#define ZS_BP_PROP_EXTFILE						(ZPROP_CUSTOM_PROPERTY_BASE + 320)
#define ZS_BP_PROP_MODEL_BASIC					(ZPROP_CUSTOM_PROPERTY_BASE + 360)
#define ZS_BP_PROP_UNIT							(ZPROP_CUSTOM_PROPERTY_BASE + 400)
#define ZS_BP_PROP_ANNUAL_NUMBER				(ZPROP_CUSTOM_PROPERTY_BASE + 440)
#define ZS_BP_PROP_COMBINATION					(ZPROP_CUSTOM_PROPERTY_BASE + 480)
#define ZS_BP_PROP_SIM_DELIVERABLE				(ZPROP_CUSTOM_PROPERTY_BASE + 520)
#define ZS_BP_PROP_SIM_PROCEDURE				(ZPROP_CUSTOM_PROPERTY_BASE + 560)
#define ZS_BP_PROP_SIM_PROCESS 					(ZPROP_CUSTOM_PROPERTY_BASE + 600)
#define ZS_BP_PROP_TASKLIST 					(ZPROP_CUSTOM_PROPERTY_BASE + 640)
#define ZS_BP_PROP_DECISIONLIST 				(ZPROP_CUSTOM_PROPERTY_BASE + 660)
#define ZS_BP_PROP_TEXTITEMLIST 				(ZPROP_CUSTOM_PROPERTY_BASE + 680)
#define ZS_BP_PROP_EXTAPP						(ZPROP_CUSTOM_PROPERTY_BASE + 720)
#define ZS_BP_PROP_QUANTITY						(ZPROP_CUSTOM_PROPERTY_BASE + 760)
#define ZS_BP_PROP_PROCEDURE_ACTIVATION			(ZPROP_CUSTOM_PROPERTY_BASE + 800)
#define ZS_BP_PROP_PROCEDURE_WORKLOAD_FORC		(ZPROP_CUSTOM_PROPERTY_BASE + 840)
#define ZS_BP_PROP_PROCEDURE_COST_FORECAST		(ZPROP_CUSTOM_PROPERTY_BASE + 880)
#define ZS_BP_PROP_SIM_PROCEDURE_COST			(ZPROP_CUSTOM_PROPERTY_BASE + 920)
#define ZS_BP_PROP_SIM_PROCESS_WORKLOAD_FORC	(ZPROP_CUSTOM_PROPERTY_BASE + 960)
#define ZS_BP_PROP_SIM_PROCESS_COST_FORECAST	(ZPROP_CUSTOM_PROPERTY_BASE + 1000)
#define ZS_BP_PROP_RULELIST 					(ZPROP_CUSTOM_PROPERTY_BASE + 1040)
#define ZS_BP_PROP_LANGUAGE 					(ZPROP_CUSTOM_PROPERTY_BASE + 1080)
// JMR-MODIF - Le 1er février 2006 - Ajout d'un ID pour la catégorie de propriétés de type prestations.
#define ZS_BP_PROP_PRESTATIONS					(ZPROP_CUSTOM_PROPERTY_BASE + 1120)
// JMR-MODIF - Le 6 février 2006 - Ajout d'un ID pour la catégorie des propriétés de type Livraisons.
#define ZS_BP_PROP_DELIVERIES					(ZPROP_CUSTOM_PROPERTY_BASE + 1160)
// JMR-MODIF - Le 22 novembre 2006 - Ajout d'un ID pour la catégorie des propriétés de type Règles.
#define ZS_BP_PROP_RULES						(ZPROP_CUSTOM_PROPERTY_BASE + 1200)
// JMR-MODIF - Le 3 juin 2007 - Ajout d'un ID pour la catégorie des propriétés de type Risques.
#define ZS_BP_PROP_RISK							(ZPROP_CUSTOM_PROPERTY_BASE + 1240)
#define ZS_BP_DYNAMICPROP_START 				(ZPROP_CUSTOM_PROPERTY_BASE + 5000)

/////////////////////////////////////////////////////////////////////////////
#endif // __ZPROPERTYIDS_H__
/////////////////////////////////////////////////////////////////////////////