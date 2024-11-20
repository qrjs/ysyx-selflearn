
typedef enum {
	SYSZ_CC_O = SYSTEMZ_CC_O,
	SYSZ_CC_H = SYSTEMZ_CC_H,

	SYSZ_CC_NH = SYSTEMZ_CC_NH,
	SYSZ_CC_NO = SYSTEMZ_CC_NO,
	SYSZ_CC_INVALID = SYSTEMZ_CC_INVALID,
} sysz_cc;

typedef enum {
	SYSZ_GRP_INVALID = SYSTEMZ_GRP_INVALID,

	SYSZ_GRP_JUMP = SYSTEMZ_GRP_JUMP,
	SYSZ_GRP_CALL = SYSTEMZ_GRP_CALL,
	SYSZ_GRP_RET = SYSTEMZ_GRP_RET,
	SYSZ_GRP_INT = SYSTEMZ_GRP_INT,
	SYSZ_GRP_IRET = SYSTEMZ_GRP_IRET,
	SYSZ_GRP_PRIVILEGE = SYSTEMZ_GRP_PRIVILEGE,
	SYSZ_GRP_BRANCH_RELATIVE = SYSTEMZ_GRP_BRANCH_RELATIVE,

	SYSZ_FEATURE_FEATURESOFTFLOAT = SYSTEMZ_FEATURE_FEATURESOFTFLOAT,
	SYSZ_FEATURE_FEATUREBACKCHAIN = SYSTEMZ_FEATURE_FEATUREBACKCHAIN,
	SYSZ_FEATURE_FEATUREDISTINCTOPS = SYSTEMZ_FEATURE_FEATUREDISTINCTOPS,
	SYSZ_FEATURE_FEATUREFASTSERIALIZATION = SYSTEMZ_FEATURE_FEATUREFASTSERIALIZATION,
	SYSZ_FEATURE_FEATURERESETDATPROTECTION = SYSTEMZ_FEATURE_FEATURERESETDATPROTECTION,
	SYSZ_FEATURE_FEATUREPROCESSORACTIVITYINSTRUMENTATION = SYSTEMZ_FEATURE_FEATUREPROCESSORACTIVITYINSTRUMENTATION,


	SYSZ_GRP_ENDING = SYSTEMZ_GRP_ENDING,
} sysz_insn_group;


typedef enum {
	SYSZ_OP_INVALID = SYSTEMZ_OP_INVALID,
	SYSZ_OP_REG = SYSTEMZ_OP_REG,
	SYSZ_OP_IMM = SYSTEMZ_OP_IMM,
	SYSZ_OP_MEM = SYSTEMZ_OP_MEM,
} sysz_op_type;

typedef enum {

	SYSZ_REG_INVALID = SYSTEMZ_REG_INVALID,
	SYSZ_REG_CC = SYSTEMZ_REG_CC,
	SYSZ_REG_FPC = SYSTEMZ_REG_FPC,
	SYSZ_REG_R12Q = SYSTEMZ_REG_R12Q,
	SYSZ_REG_R14Q = SYSTEMZ_REG_R14Q,
	SYSZ_REG_ENDING = SYSTEMZ_REG_ENDING,


} sysz_reg;

typedef systemz_suppl_info sysz_suppl_info;

typedef systemz_op_mem sysz_op_mem;

typedef cs_systemz_op cs_sysz_op;

#define MAX_SYSZ_OPS 6

typedef cs_systemz cs_sysz;

typedef enum {

	SYSZ_INS_INVALID = SYSTEMZ_INS_INVALID,
	SYSZ_INS_A = SYSTEMZ_INS_A,
	SYSZ_INS_ZAP = SYSTEMZ_INS_ZAP,


	SYSZ_INS_ENDING = SYSTEMZ_INS_ENDING,

	SYSZ_INS_ALIAS_BEGIN = SYSTEMZ_INS_ALIAS_BEGIN,

	SYSZ_INS_ALIAS_VISTRB = SYSTEMZ_INS_ALIAS_VISTRB,
	SYSZ_INS_ALIAS_VSTRCZFS = SYSTEMZ_INS_ALIAS_VSTRCZFS,
	SYSZ_INS_ALIAS_VSTRSH = SYSTEMZ_INS_ALIAS_VSTRSH,
	SYSZ_INS_ALIAS_VSTRSF = SYSTEMZ_INS_ALIAS_VSTRSF,



	SYSZ_INS_ALIAS_END = SYSTEMZ_INS_ALIAS_END,
} sysz_insn;

