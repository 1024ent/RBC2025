/**
 * @file stepper.h
 * @brief Managing Stepper Motor behaviour
 * @copyright UMPSA ROBOTICS
 * @license Apache-2.0
 * @author Loo Hui Kie [ELPROG]
 */

#ifndef __STEPPER_H__
#define __STEPPER_H__

#include <stdlib.h>
#include <Arduino.h>

class Stepper {
public:
    /// \brief Symbolic pin names for motor interfaces.
    /// Use these names in the AccelStepper constructor for pin configuration.
    typedef enum
    {
        FUNCTION  = 0, ///< Custom driver functions (internal use).
        DRIVER    = 1, ///< Stepper driver with 2 pins.
        FULL2WIRE = 2, ///< 2-wire stepper (2 pins).
        FULL3WIRE = 3, ///< 3-wire stepper (e.g., HDD spindle).
        FULL4WIRE = 4, ///< 4-wire full stepper (4 pins).
        HALF3WIRE = 6, ///< 3-wire half stepper (e.g., HDD spindle).
        HALF4WIRE = 8  ///< 4-wire half stepper (4 pins).
    } MotorInterfaceType;

    /// Constructor for stepper motor. Supports simultaneous steppers with different speeds/accelerations. 
    /// Default pins are 2, 3, 4, 5 and interface is FULL4WIRE (4 pins).
    /// \param[in] interface Motor interface type. 
    /// \param[in] pin1-4 Motor pin numbers. Defaults to 2, 3, 4, 5.
    /// \param[in] enable If true, enables motor pins at construction.
    Stepper(uint8_t interface = Stepper::FULL4WIRE, uint8_t pin1 = 2, uint8_t pin2 = 3, uint8_t pin3 = 4, uint8_t pin4 = 5, bool enable = true);

    /// Alternate constructor for custom step functions. No pins are initialized.
    /// \param[in] forward Procedure for a forward step.
    /// \param[in] backward Procedure for a backward step.
    Stepper(void (*forward)(), void (*backward)());

    /// Sets the target position.
    /// \param[in] absolute Desired absolute position (negative = anticlockwise).
    void moveTo(long absolute);

    /// Sets a relative target position.
    /// \param[in] relative Position relative to the current position (negative = anticlockwise).
    void move(long relative);

    /// Polls and steps the motor based on speed and time. Call in your main loop.
    /// \return true if the motor is still moving.
    boolean run();

    /// Polls and steps the motor at constant speed.
    /// \return true if the motor stepped.
    boolean runSpeed();

    /// Sets the maximum speed.
    /// \param[in] speed Max speed in steps/second.
    void setMaxSpeed(float speed);

    /// Gets the current maximum speed.
    /// \return Current max speed in steps/second.
    float maxSpeed();

    /// Sets the acceleration.
    /// \param[in] acceleration Acceleration in steps/second².
    void setAcceleration(float acceleration);

    /// Sets constant speed for runSpeed().
    /// \param[in] speed Speed in steps/second (positive = clockwise).
    void setSpeed(float speed);

    /// Gets the most recent speed.
    /// \return Last set speed in steps/second.
    float speed();

    /// Gets the distance to the target position.
    /// \return Distance in steps to the target position.
    long distanceToGo();

    /// Gets the most recent target position.
    /// \return Target position in steps.
    long targetPosition();

    /// Gets the current motor position.
    /// \return Current position in steps.
    long currentPosition();  

    /// Resets the current position to a new value.
    /// \param[in] position New position in steps.
    void setCurrentPosition(long position);  

    /// Moves the motor to the target position, blocking until reached.
    void runToPosition();

    /// Moves the motor to the target position at constant speed.
    /// \return true if the motor stepped.
    boolean runSpeedToPosition();

    /// Moves the motor to a new position and blocks until reached.
    /// \param[in] position New target position.
    void runToNewPosition(long position);

    /// Stops the motor as quickly as possible.
    void stop();

    /// Disables motor pin outputs (low power).
    /// Useful for sleep modes, re-enable with enableOutputs().
    virtual void disableOutputs();

    /// Enables motor pin outputs.
    /// Automatically called by constructor.
    virtual void enableOutputs();

    /// Sets the minimum pulse width.
    /// \param[in] minWidth Minimum pulse width in microseconds.
    void setMinPulseWidth(unsigned int minWidth);

    /// Sets the enable pin for stepper drivers.
    /// \param[in] enablePin Pin number for motor enable.
    void setEnablePin(uint8_t enablePin = 0xff);

    /// Sets inversion for stepper driver pins.
    /// \param[in] directionInvert, stepInvert, enableInvert Pin inversion flags.
    void setPinsInverted(bool directionInvert = false, bool stepInvert = false, bool enableInvert = false);

    /// Sets inversion for 2, 3, and 4-wire stepper pins.
    /// \param[in] pin1-4Invert Pin inversion flags.
    /// \param[in] enableInvert Enable pin inversion.
    void setPinsInverted(bool pin1Invert, bool pin2Invert, bool pin3Invert, bool pin4Invert, bool enableInvert);

    /// Checks if the motor is running.
    /// \return true if the motor is still running.
    bool isRunning();

    protected:

    /// Direction indicator for motor rotation
    typedef enum
    {
        DIRECTION_CCW = 0,  ///< Counter-Clockwise
        DIRECTION_CW  = 1   ///< Clockwise
    } Direction;

    /// Updates motor speed after various changes (step, maxSpeed, acceleration, position)
    void computeNewSpeed();

    /// Sets motor output pins based on the mask
    virtual void setOutputPins(uint8_t mask);

    /// Executes a step for motor; subclasses can override for custom stepping
    virtual void step(long step);

    /// Executes a step with stepper functions (pins = 0)
    virtual void step0(long step);

    /// Executes a step for stepper driver (pins = 1)
    virtual void step1(long step);

    /// Executes a step for a 2-pin motor
    virtual void step2(long step);

    /// Executes a step for a 3-pin motor (e.g., HDD spindle)
    virtual void step3(long step);

    /// Executes a step for a 4-pin motor
    virtual void step4(long step);

    /// Executes a step for a 3-pin motor (e.g., HDD spindle)
    virtual void step6(long step);

    /// Executes a step for a 4-pin half-step motor
    virtual void step8(long step);

    /// Current motor direction (1 = CW)
    boolean _direction;
    
    private:
    /// Number of pins for stepper motor (2 for bipolar, 4 for unipolar)
    uint8_t _interface;          // 0, 1, 2, 4, 8, See MotorInterfaceType

    /// Arduino pin assignments for stepper motor or driver
    uint8_t _pin[4];

    /// Whether each pin is inverted
    uint8_t _pinInverted[4];

    /// Current position in steps
    long _currentPos;    // Steps

    /// Target position in steps for the motor to move to
    long _targetPos;     // Steps

    /// Current motor speed in steps per second (clockwise is positive)
    float _speed;         // Steps per second

    /// Maximum allowed speed in steps per second
    float _maxSpeed;

    /// Acceleration in steps per second squared
    float _acceleration;
    float _sqrt_twoa; // Precomputed sqrt(2*_acceleration)

    /// Current interval between steps in microseconds (0 if stopped)
    unsigned long _stepInterval;

    /// Last step time in microseconds
    unsigned long _lastStepTime;

    /// Minimum pulse width in microseconds
    unsigned int _minPulseWidth;

    /// Direction pin inversion (moved to _pinInverted[1])
    bool _enableInverted;

    /// Enable pin for stepper driver, 0xFF if unused
    uint8_t _enablePin;

    /// Forward step procedure pointer
    void (*_forward)();

    /// Backward step procedure pointer
    void (*_backward)();

    /// Step counter for speed calculations
    long _n;

    /// Initial step size in microseconds
    float _c0;

    /// Last step size in microseconds
    float _cn;

    /// Minimum step size at max speed
    float _cmin; // at max speed
};

#endif 