#ifndef TRACERMANAGER_H
#define TRACERMANAGER_H

#include <optional>
#include <vector>
#include <QObject>

class Tracer;
class libusb_context;
enum libusb_transfer_status;
class APDUCommand;
class APDUResponse;

/** A manager class for all tracers connected to
  * the system.
  *
  * @b Description
  * The manager class will send notifications when  
  * tracers are hotplugged.
  *
  */
class TracerManager : public QObject {
	Q_OBJECT

signals:
	/**
	 * Emitted when the tracer successfully starts sniffing.
	 *
	 * @param tracer	The tracer that has started sniffing.
	 */
	void tracerStartedSniffing(Tracer *);
	
	/**
	 * Emitted when the tracer stops sniffing for whatever
	 * reason. This is only emmitted if the trace session has 
	 * started and then failed. If the trace session hasn't been
	 * successfully started, `startSniffing()` will return the
	 * error code for this. If a non-zero error code is returned, 
	 * the trace session has been stopped due to an error.
	 *
	 * @param tracer		The tracer that has started sniffing.
	 * @param errorCode		libusb_transfer_status code if any.
	 */
	void tracerStoppedSniffing(Tracer *tracer, libusb_transfer_status errorCode);

	/**
	 * Emitted when a trace has begun and the SIM card has
	 * already been sending commands to the tracer, but
	 * because we have not been listening for them, we find
	 * ourselves at an arbitrary point in the trace. This may
	 * make the APDUSplitter misbehave and thus return incorrect
	 * values.
	 *
	 * @param tracer	The tracer that has started mid session.
	 */
	void traceStartedMidSession(Tracer *tracer);

	/**
	 * Emitted when an APDU command-response pair has been
	 * successfully recieved and split.
	 *
	 * @param tracer	The tracer that has received the command.
	 * @param output	The output string that should be presented to the user.
	 * @param command	The APDU command.
	 * @param response	The APDU response.
	 */
	void apduCommandRecieved(Tracer *tracer,
		const QString &output,
		const APDUCommand &command,
		const APDUResponse &response);

	/**
	 * Emitted when an ATR command has been received from the tracer.
	 *
	 * @param tracer	The tracer that has received the command.
	 * @param output	The output string that should be presented to the user.
	 */
	void atrCommandReceived(Tracer *tracer, const QString &output);

public:
	/** The shared manager instance */
	static TracerManager & sharedManager() {
		static TracerManager instance;
		return instance;
	}

	// prevent accidental copies
	TracerManager(TracerManager const&) = delete;
	void operator=(TracerManager const&) = delete;

	/**
	 * Finds a tracer connected to the system.
	 *
	 * @retval	A Tracer object if a tracer is found. Otherwise,
	 *			an empty optional.
	 */
	std::optional<Tracer *>findTracer();

	/**
	 * Starts sniffing SIM requests. `tracerStartedSniffing` will
	 * be emitted upon success.
	 *
	 * @param tracer	The tracer that is to start sniffing.
	 *
	 * @retval	A libusb_error status code. Returns `0` for success.
	 */
	int startSniffing(Tracer *tracer);

	/**
	 * Stops sniffing requests. 
	 *
	 * @Note	This function starts an asyncronous call. This
	 * means that the sniffing session is not guarenteed to 
	 * immediately finish when this method returns. `tracerStoppedSniffing`
	 * will be emitted when the tracer fully stops sniffing. 
	 *
	 * @param tracer	The tracer that is to stop sniffing.
	 */
	void stopSniffing(Tracer *tracer);

private:
	TracerManager();
	TracerManager(QObject *parent) = delete;
	~TracerManager();
	std::vector<Tracer *>tracers;
	libusb_context *context;

	void manageTracer(Tracer *tracer);
	void stopManagingTracer(Tracer *tracer);
	bool isManagingTracer(Tracer *tracer);
};

#endif // TRACERMANAGER_H
