package org.atriasoft.esvg.internal;

import io.scenarium.logger.LogLevel;
import io.scenarium.logger.Logger;

public class Log {
	private static final String LIBNAME = "esvg";
	private static final String LIBNAMEDRAW = Logger.getDrawableName(Log.LIBNAME);
	private static final boolean PRINTCRITICAL = Logger.getNeedPrint(Log.LIBNAME, LogLevel.CRITICAL);
	private static final boolean PRINTDEBUG = Logger.getNeedPrint(Log.LIBNAME, LogLevel.DEBUG);
	private static final boolean PRINTERROR = Logger.getNeedPrint(Log.LIBNAME, LogLevel.ERROR);
	private static final boolean PRINTINFO = Logger.getNeedPrint(Log.LIBNAME, LogLevel.INFO);
	private static final boolean PRINTPRINT = Logger.getNeedPrint(Log.LIBNAME, LogLevel.PRINT);
	private static final boolean PRINTTODO = Logger.getNeedPrint(Log.LIBNAME, LogLevel.TODO);
	private static final boolean PRINTVERBOSE = Logger.getNeedPrint(Log.LIBNAME, LogLevel.VERBOSE);
	private static final boolean PRINTWARNING = Logger.getNeedPrint(Log.LIBNAME, LogLevel.WARNING);
	
	public static void critical(final String data) {
		if (Log.PRINTCRITICAL) {
			Logger.critical(Log.LIBNAMEDRAW, data);
		}
	}
	
	public static void debug(final String data) {
		if (Log.PRINTDEBUG) {
			Logger.debug(Log.LIBNAMEDRAW, data);
		}
	}
	
	public static void error(final String data) {
		if (Log.PRINTERROR) {
			Logger.error(Log.LIBNAMEDRAW, data);
		}
	}
	
	public static void info(final String data) {
		if (Log.PRINTINFO) {
			Logger.info(Log.LIBNAMEDRAW, data);
		}
	}
	
	public static void print(final String data) {
		if (Log.PRINTPRINT) {
			Logger.print(Log.LIBNAMEDRAW, data);
		}
	}
	
	public static void todo(final String data) {
		if (Log.PRINTTODO) {
			Logger.todo(Log.LIBNAMEDRAW, data);
		}
	}
	
	public static void verbose(final String data) {
		if (Log.PRINTVERBOSE) {
			Logger.verbose(Log.LIBNAMEDRAW, data);
		}
	}
	
	public static void warning(final String data) {
		if (Log.PRINTWARNING) {
			Logger.warning(Log.LIBNAMEDRAW, data);
		}
	}
	
	private Log() {}
	
}
