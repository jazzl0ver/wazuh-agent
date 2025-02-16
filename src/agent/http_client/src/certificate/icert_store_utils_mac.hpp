#pragma once

#include <CoreFoundation/CoreFoundation.h>
#include <Security/Security.h>

#include <string>

namespace https_socket_verify_utils
{
    /// @brief Interface for certificate utility functions.
    ///
    /// This interface defines methods for handling certificate chains, encoding certificates,
    /// creating trust objects, evaluating trust, and working with `CFTypeRef` and `CFStringRef`
    /// objects in the context of SSL/TLS certificate verification.
    class ICertificateStoreUtilsMac
    {
    public:
        /// @brief Virtual destructor.
        virtual ~ICertificateStoreUtilsMac() = default;

        /// @brief Creates a SecCertificateRef from the given certificate data.
        ///
        /// @param certData The raw certificate data in CFDataRef format.
        /// @return A SecCertificateRef object representing the certificate.
        virtual SecCertificateRef CreateCertificate(CFDataRef certData) const = 0;

        /// @brief Creates a trust object for the given certificates and policy.
        ///
        /// @param certs The array of certificates.
        /// @param policy The SecPolicyRef object defining the policy.
        /// @param trust The SecTrustRef object to be created.
        /// @return An OSStatus indicating success or failure.
        virtual OSStatus CreateTrustObject(CFArrayRef certs, SecPolicyRef policy, SecTrustRef* trust) const = 0;

        /// @brief Evaluates the trust status of the given trust object.
        ///
        /// @param trust The SecTrustRef object representing the trust object.
        /// @param error A pointer to a CFErrorRef to capture any error during evaluation.
        /// @return `true` if the trust evaluation succeeded, otherwise `false`.
        virtual bool EvaluateTrust(SecTrustRef trust, CFErrorRef* error) const = 0;

        /// @brief Creates a CFDataRef from the given certificate data and length.
        ///
        /// @param certData The certificate data in unsigned char array format.
        /// @param certLen The length of the certificate data.
        /// @return A CFDataRef object containing the certificate data.
        virtual CFDataRef CreateCFData(const unsigned char* certData, int certLen) const = 0;

        /// @brief Creates a CFArrayRef from an array of certificate values.
        ///
        /// @param certArrayValues The array of certificate values.
        /// @param count The number of elements in the array.
        /// @return A CFArrayRef object containing the certificates.
        virtual CFArrayRef CreateCertArray(const void* certArrayValues[], size_t count) const = 0;

        /// @brief Retrieves a description of the error in a CFErrorRef object.
        ///
        /// @param error The CFErrorRef object representing the error.
        /// @return A CFStringRef containing the error description.
        virtual CFStringRef CopyErrorDescription(CFErrorRef error) const = 0;

        /// @brief Retrieves the subject summary (SAN or CN) of the given certificate.
        ///
        /// @param cert The SecCertificateRef object representing the certificate.
        /// @return A CFStringRef containing the subject summary.
        virtual CFStringRef CopySubjectSummary(SecCertificateRef cert) const = 0;

        /// @brief Converts a CFStringRef to a std::string.
        ///
        /// @param cfString The CFStringRef to convert.
        /// @return A std::string containing the UTF-8 encoded string.
        virtual std::string GetStringCFString(CFStringRef cfString) const = 0;

        /// @brief Releases a CFTypeRef object.
        ///
        /// @param cfObject The CFTypeRef object to release.
        virtual void ReleaseCFObject(CFTypeRef cfObject) const = 0;

        /// @brief Creates an SSL policy for the given hostname.
        ///
        /// @param server A boolean indicating whether the policy is for a server (true) or client (false).
        /// @param hostname The hostname to use for the policy. If null, defaults to no hostname.
        /// @return A SecPolicyRef object representing the SSL policy.
        virtual SecPolicyRef CreateSSLPolicy(bool server, const std::string& hostname) const = 0;
    };

} // namespace https_socket_verify_utils
