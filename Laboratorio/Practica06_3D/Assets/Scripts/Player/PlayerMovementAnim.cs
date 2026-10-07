using UnityEngine;

public class PlayerMovementAnim : MonoBehaviour
{
    public Transform cameraTransform;
    Animator anim;
    CharacterController controller;

    void Start()
    {
        anim = GetComponent<Animator>();
        controller = GetComponent<CharacterController>();
    }

    void Update()
    {
        float x = Input.GetAxis("Horizontal");
        float z = Input.GetAxis("Vertical");
        Vector3 camForward = cameraTransform.forward;
        Vector3 camRight = cameraTransform.right;
        camForward.y = 0f;
        camRight.y = 0f;
        camForward.Normalize();
        camRight.Normalize();
        Vector3 moveDir = camForward * z + camRight * x;
        // Sin esta linea el personaje no se moverá de su posicion

        controller.Move(moveDir * Time.deltaTime * 3f);

        float speedValue = moveDir.magnitude;
        anim.SetFloat("Speed", speedValue);

        if (moveDir.magnitude > 0.1f)
        {
            Quaternion targetRotation = Quaternion.LookRotation(moveDir);
            transform.rotation = Quaternion.Slerp(
            transform.rotation,
            targetRotation,
            Time.deltaTime * 10f
            );
        }



        if (Input.GetKey(KeyCode.LeftShift))
        {
            speedValue = 1f;
        }
        else if (speedValue > 0)
        {
            speedValue = 0.5f;
        }
        else
        {
            speedValue = 0f;
        }

        anim.SetFloat("Speed", speedValue);

        if (Input.GetKeyDown(KeyCode.Space))
        {
            anim.SetBool("IsJumping", true);
        }
        else
        {
            anim.SetBool("IsJumping", false);
        }
    }
}